﻿#include "module.hpp"
#include "state.hpp"
#undef MessageBox

namespace win_api
{
	struct LUA_WIN32_FIND_DATAW {
		WIN32_FIND_DATAW data;
		static int lua_index(lua_State* L) {

			ARG_CPPDATA(1, LUA_WIN32_FIND_DATAW, data);
			METATABLE_BEGIN(WIN32_FIND_DATAW, (*data).data);
			METATABLE_INDEX(stdwstring, cFileName, std::wstring);
			METATABLE_END();
		}
		static int lua_newindex(lua_State* L) {
			METATABLE_END();
		}

	};
	static int AllocConsole(lua_State* L) {
		local.allocConsole = true;
		::AllocConsole();
		return 0;
	}

	static int FreeConsole(lua_State* L) {
		local.allocConsole = false;
		::FreeConsole();
		return 0;
	}

	static int GetAsyncKeyState(lua_State* L) {
		ARG(1, integer, int32_t, vKey);
		RET(integer, ::GetAsyncKeyState(vKey));
	}

	static int GetKeyState(lua_State* L) {
		ARG(1, integer, int32_t, nVirtKey);
		RET(integer, ::GetKeyState(nVirtKey));
	}

	static int MessageBox(lua_State* L) {
		ARG(1, integer, HWND, hWnd);
		ARG(2, string, LPCSTR, lpText);
		ARG(3, string, LPCSTR, lpCaption);
		ARG(4, integer, UINT, uType);

		size_t len_t = utils::U8ToU16(lpText);
		vector<wchar_t> u16_t(len_t);
		utils::U8ToU16(lpText, u16_t.data(), len_t);

		size_t len_c = utils::U8ToU16(lpCaption);
		vector<wchar_t> u16_c(len_c);
		utils::U8ToU16(lpCaption, u16_c.data(), len_c);

		RET(integer, MessageBoxW(hWnd, u16_t.data(), u16_c.data(), uType));
	}

	static int GenerateTempFileName(lua_State* L) {
		ARG_DEF(1, stdstring, std::string, prefix, {});
		ARG_DEF(2, stdstring, std::string, suffix, {});

		auto wprefix = utils::U8ToU16(prefix);
		auto wsuffix = utils::U8ToU16(suffix);
		wchar_t tmppath[MAX_PATH - 14]{};
		GetTempPathW(MAX_PATH - 13, tmppath);
		wchar_t filename[MAX_PATH + 5]{};
		GetTempFileNameW(tmppath, wprefix.c_str(), 0, filename);
		std::wstring wres = filename + wsuffix;
		RET(stdstring, utils::U16ToU8(wres));
	}

	static int WriteFile(lua_State* L) {
		ARG(1, stdstring, std::string, path);
		ARG(2, stdstringview, std::string_view, data);
		ARG_DEF(3, boolean, bool, append, false);

		DWORD dwFlags = CREATE_ALWAYS;
		if (append) dwFlags = OPEN_ALWAYS;
		HANDLE hFile = CreateFileW(utils::U8ToU16(path).c_str(), GENERIC_WRITE, 0, nullptr, dwFlags, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE) [[unlikely]] {
			RET(integer, 0);
			}
		if (append) SetFilePointer(hFile, 0, nullptr, FILE_END);
		DWORD bytes = 0;
		::WriteFile(hFile, data.data(), data.size(), &bytes, nullptr);
		CloseHandle(hFile);
		RET(integer, bytes);
	}

	static int ReadFile(lua_State* L) {
		ARG(1, stdstring, std::string, path);
		ARG(2, integer, size_t, offset);
		ARG_DEF(3, integer, size_t, size, 4096);

		HANDLE hFile = CreateFileW(utils::U8ToU16(path).c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE) [[unlikely]] {
			RET(stdstring, {});
			}
		SetFilePointer(hFile, offset, nullptr, FILE_BEGIN);
		std::string fdata(size, '\0');
		DWORD bytes = 0;
		::ReadFile(hFile, fdata.data(), fdata.size(), &bytes, nullptr);
		CloseHandle(hFile);
		RET(stdstring, std::string(fdata, bytes));
	}

	static int GetTickCount(lua_State* L) {
		RET(integer, ::GetTickCount64());
	}

#undef FindFirstFile
	static int FindFirstFile(lua_State* L) {
		ARG(1, stdwstring, std::wstring, lpFileName);
		auto findData = NEW_CPPDATA(LUA_WIN32_FIND_DATAW);
		local.lua.lua_pushinteger(L, (LUA_INTEGER)FindFirstFileW(lpFileName.c_str(), &(*findData).data));
		local.lua.lua_pushvalue(L, -2);
		return 2;
	}
#undef FindNextFile
	static int FindNextFile(lua_State* L) {
		ARG(1, integer, HANDLE, hFindFile);
		auto findData = NEW_CPPDATA(LUA_WIN32_FIND_DATAW);
		local.lua.lua_pushboolean(L, FindNextFileW(hFindFile, &(*findData).data));
		local.lua.lua_pushvalue(L, -2);
		return 2;
	}

	static int FindClose(lua_State* L) {
		ARG(1, integer, HANDLE, hFindFile);
		RET(boolean, ::FindClose(hFindFile));
	}

	static RegisterModule Init = [] {
		MODULE_BEGIN(WinAPI);
		MODULE_FUNC(AllocConsole);
		MODULE_FUNC(FreeConsole);
		MODULE_FUNC(GetAsyncKeyState);
		MODULE_FUNC(GetKeyState);
		MODULE_FUNC(MessageBox);
		MODULE_FUNC(GenerateTempFileName);
		MODULE_FUNC(WriteFile);
		MODULE_FUNC(ReadFile);
		MODULE_FUNC(GetTickCount);
		MODULE_FUNC(FindFirstFile);
		MODULE_FUNC(FindNextFile);
		MODULE_FUNC(FindClose);
		MODULE_END();
		};
}
