#include "utils.hpp"
#include <fstream>
#include <ostream>

namespace {

template <class T>
bool writeMem(size_t address, T value)
{
	*(T*)(address) = value;
	return true;
}

template <class T>
T* pointMem(size_t address)
{
	return (T*)address;
}

template <class T>
T readMem(size_t address)
{
	return *(T*)address;
}

template <class T>
DWORD protectMem(size_t address, DWORD protection)
{
	DWORD oldProtection;
	VirtualProtect((LPVOID)address, sizeof(T), protection, &oldProtection);
	return oldProtection;
}

bool getTemporaryFileName(std::wstring& output)
{
	output = L"";

	wchar_t tempPath[MAX_PATH + 1];
	if (GetTempPathW(sizeof(tempPath) / sizeof(wchar_t), tempPath) == 0)
		return false;

	wchar_t tempFile[MAX_PATH + 1];
	if (GetTempFileNameW(tempPath, L"cln", 0, tempFile) == 0)
		return false;

	output = tempFile;
	return true;
}

void copyFile(const std::wstring& source, const std::wstring& dest)
{
	std::ifstream src(source.c_str(), std::ios::binary);
	std::ofstream dst(dest.c_str(), std::ios::binary);
	dst << src.rdbuf();
}

bool fileExists(const std::wstring& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

HMODULE cloneLibrary(const char* libraryName)
{
    // get the full path to the target module
    auto targetMod = GetModuleHandleA(libraryName);
    wchar_t targetName[MAX_PATH + 1];
    if (!GetModuleFileNameW(targetMod, targetName, sizeof(targetName) / sizeof(wchar_t)))
        return nullptr;

    // make a copy of it in the temp directory
    std::wstring newdllname;
    if (!getTemporaryFileName(newdllname))
        return nullptr;

    copyFile(targetName, newdllname);
    if (!fileExists(newdllname))
        return nullptr;

    // load and ret
    return LoadLibraryW(newdllname.c_str());
}

std::unordered_map<std::string, FILETIME> libraryLoadTime;

}

HMODULE reloadLibraryMain(const char* libraryName, bool checkTimestamp)
{
    auto targetMod = GetModuleHandleA(libraryName);
    wchar_t targetName[MAX_PATH + 1];
    if (!GetModuleFileNameW(targetMod, targetName, sizeof(targetName) / sizeof(wchar_t))) [[unlikely]] {
        return nullptr;
    }

    if (checkTimestamp) { // check if the file is newer than last write time
        FILETIME writeTime;
        HANDLE hFile = CreateFileW(targetName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) [[unlikely]] {
            return nullptr;
        }
        if (!GetFileTime(hFile, NULL, NULL, &writeTime)) [[unlikely]] {
            return nullptr;
        }
        auto it = libraryLoadTime.find(libraryName);
        if (it != libraryLoadTime.end()) {
            if (CompareFileTime(&it->second, &writeTime) >= 0) {
                return nullptr;
            }
            Sleep(1000); // wait for the file to be fully written
            it->second = writeTime;
        } else {
            libraryLoadTime.emplace(libraryName, writeTime);
            return nullptr;
        }
    }

    // make a copy of it in the temp directory
    std::wstring newdllname;
    if (!getTemporaryFileName(newdllname)) [[unlikely]] {
        return nullptr;
    }

    copyFile(targetName, newdllname);
    if (!fileExists(newdllname)) [[unlikely]] {
        return nullptr;
    }

    // load new library
    auto newMod = LoadLibraryW(newdllname.c_str());
    // free old library
    /* FreeLibrary(targetMod); */
    return newMod;
}

size_t reloadLibraryImports(const char* libraryName, void* _mod)
{
	auto mod = (size_t)(_mod);
	if (!mod)
		mod = (size_t)GetModuleHandle(NULL);

	// locate PE
	auto dosHeader = pointMem<IMAGE_DOS_HEADER>(mod);
	if (dosHeader->e_magic != 0x5A4D)
		return 0;

	auto optionalHeader = pointMem<IMAGE_OPTIONAL_HEADER>(mod + dosHeader->e_lfanew + 24);
	if (optionalHeader->Magic != 0x10B)
		return 0;

	if (optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size == 0 ||
		optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress == 0)
		return 0;

	// scan imports for the target library and clone it
	HMODULE clone = nullptr;
	auto importDescriptor = pointMem<IMAGE_IMPORT_DESCRIPTOR>(mod + optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	while (importDescriptor->FirstThunk)
	{
		auto importLibraryName = pointMem<char>(mod + importDescriptor->Name);
		if (!_stricmp(libraryName, importLibraryName))
		{
			clone = cloneLibrary(libraryName);
			break;
		}
		else
			importDescriptor++;
	}

	if (!clone || !importDescriptor || !importDescriptor->FirstThunk)
		return 0;

	size_t n = 0;
	size_t replaced = 0;
	auto thunkData = pointMem<IMAGE_THUNK_DATA>(mod + importDescriptor->OriginalFirstThunk);
	while (thunkData->u1.Function)
	{
		auto importFunctionName = pointMem<char>(mod + thunkData->u1.AddressOfData + 2);
		auto address = (size_t)pointMem<size_t>(mod + importDescriptor->FirstThunk + (n * sizeof(DWORD)));
		auto newFunction = GetProcAddress(clone, importFunctionName);

		if (newFunction)
		{
			auto old = protectMem<FARPROC>(address, PAGE_EXECUTE_READWRITE);
			writeMem<FARPROC>(address, newFunction);
			protectMem<FARPROC>(address, old);
			replaced++;
		}

		n++;
		thunkData++;
	}

	return replaced;
}
