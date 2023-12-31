#pragma once

#include "module.hpp"

namespace system_
{

	//系统控制台输出
	static int ConsoleOutput(lua_State* L) {
		if (GetConsoleWindow())
		{
			ARG(1, string, const char*, text);
			utils::Utf8Cprintf(text);
		}
		return 0;
	}

	//获取剪贴板
	static int GetClipboard(lua_State* L) {
		local.lua.lua_pushnil(L);

		if (!OpenClipboard(nullptr)) {
			//无法打开剪贴板
			return 1;
		}

		HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
		if (!hClipboardData) {
			//无法获取剪贴板数据
			CloseClipboard();
			return 1;
		}

		wchar_t* u16 = (wchar_t*)(GlobalLock(hClipboardData));
		if (u16 == nullptr) {
			//无法锁定剪贴板
			CloseClipboard();
			return 1;
		}

		size_t len = utils::U16ToU8(u16);
		vector<char> u8(len);
		utils::U16ToU8(u16, u8.data(), len);

		GlobalUnlock(hClipboardData);
		CloseClipboard();

		local.lua.lua_pushstring(L, u8.data());

		return 1;
	}

	static int SetClipboard(lua_State* L) {
		if (!OpenClipboard(nullptr)) {
			//无法打开剪贴板
			return 0;
		}

		EmptyClipboard();
		ARG_DEF(1, string, const char*, text, "");
		size_t size = utils::U8ToU16(text);
		HGLOBAL hClipboardData = GlobalAlloc(GMEM_MOVEABLE, size * sizeof(wchar_t));
		if (!hClipboardData) {
			//无法分配内存
			CloseClipboard();
			return 0;
		}

		wchar_t* u16 = (wchar_t*)(GlobalLock(hClipboardData));

		if (!u16) {
			//无法锁定内存
			GlobalFree(hClipboardData);
			CloseClipboard();
			return 0;
		}

		utils::U8ToU16(text, u16, size);

		GlobalUnlock(hClipboardData);

		// 将数据放入剪贴板
		SetClipboardData(CF_UNICODETEXT, hClipboardData);

		// 关闭剪贴板
		CloseClipboard();

		return 0;
	}

	static void Init() {
        DEFMOD(System);
		DEF(ConsoleOutput);
		DEF(GetClipboard);
		DEF(SetClipboard);
        ENDMOD();
	}
};
