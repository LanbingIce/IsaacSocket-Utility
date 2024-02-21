#pragma once
#include "pch.h"

namespace utils {
	static std::string ToHexString(uint32_t num)
	{
		std::ostringstream oss;
		oss << std::hex << std::setiosflags(std::ios::uppercase) << num;
		return oss.str();
	}

	// 只能传入一个或三个参数，若传入一个参数，则返回转换后的长度(包括\0)
	static size_t AnsiToU16(const char* ansi, wchar_t* u16 = nullptr, size_t len = 0) {
		return MultiByteToWideChar(CP_ACP, 0, ansi, -1, u16, len);
	}

	// 只能传入一个或三个参数，若传入一个参数，则返回转换后的长度(包括\0)
	static size_t U8ToU16(const char* u8, wchar_t* u16 = nullptr, size_t len = 0) {
		return MultiByteToWideChar(CP_UTF8, 0, u8, -1, u16, len);
	}

	// 只能传入一个或三个参数，若传入一个参数，则返回转换后的长度(包括\0)
	static size_t U16ToU8(const wchar_t* u16, char* u8 = nullptr, size_t len = 0) {
		return WideCharToMultiByte(CP_UTF8, 0, u16, -1, u8, len, nullptr, nullptr);
	}

    static std::wstring AnsiToU16(std::string const &ansi) {
        std::wstring u16(utils::AnsiToU16(ansi.c_str()), L'\0');
        utils::AnsiToU16(ansi.c_str(), u16.data(), u16.size());
        return u16;
    }

    static std::wstring U8ToU16(std::string const &u8) {
        std::wstring u16(utils::U8ToU16(u8.c_str()), L'\0');
        utils::U8ToU16(u8.c_str(), u16.data(), u16.size());
        return u16;
    }

	static std::string U16ToU8(std::wstring const &u16) {
        std::string u8(utils::U16ToU8(u16.c_str()), '\0');
        utils::U16ToU8(u16.c_str(), u8.data(), u8.size());
        return u8;
    }

	static void Utf8Cprintf(const char* format, ...) {
		va_list v;
		va_start(v, format);
		size_t len = vsnprintf(nullptr, 0, format, v) + 1;
		vector<char> u8(len);
		vsnprintf(u8.data(), len, format, v);
		va_end(v);
		len = U8ToU16(u8.data());
		vector<wchar_t> u16(len);
		U8ToU16(u8.data(), u16.data(), len);
		_cwprintf(L"%s", u16.data());
	}

	static string GetDataFilePath(const char* fileName) {
		wchar_t c_path[MAX_PATH];
		GetEnvironmentVariableW(L"APPDATA", c_path, MAX_PATH);
		std::filesystem::path path = std::filesystem::path(c_path) / "IsaacSocket" / fileName;
		return (const char*)path.u8string().c_str();
	}

	// 折叠表达式打印可变参数列表
	template <typename... Args>
	void cw(const Args&... args) {
		if (GetConsoleWindow())
		{
			std::ostringstream oss;
			((oss << args << " "), ...);
			oss << '\n';
			Utf8Cprintf(oss.str().c_str());
		}
	}

	// 将文本写入指定文件
	static void WriteFile(const string& filePath, const string& text)
	{
		std::ofstream ofs(std::filesystem::path((const char8_t*)filePath.c_str()));
		if (!ofs)
		{
			return;
		}
		ofs << text;
		ofs.close();
	}

	// 读取指定文件的文本
	static std::string ReadFile(const string& filePath, const char* defaultText = "") {

		if (!std::filesystem::exists(filePath))
		{
			WriteFile(filePath, defaultText);
		}

		std::ifstream ifs(std::filesystem::path((const char8_t*)filePath.c_str()));

		if (!ifs)
		{
			return defaultText;
		}

		std::ostringstream oss;

		oss << ifs.rdbuf();
		ifs.close();

		return oss.str();
	}

}

#define FUNC(offset,ret,convention,...) auto f_##offset=(ret(convention*)(__VA_ARGS__))((char*)local.isaac+offset)
#define FIELD(address,type,name) struct{char pad_##address[address];type name;}
#define VAR_WRITE(var,value) if(var!=value){DWORD oldProtect;VirtualProtect(&var,sizeof(var),PAGE_READWRITE,&oldProtect);var=value;VirtualProtect(&var,sizeof(var),oldProtect,&oldProtect);}

using utils::cw;
