#pragma once

#include "module.hpp"

namespace win_api
{
	static int AllocConsole(lua_State* L) {
		::AllocConsole();
		return 0;
	}

	static int FreeConsole(lua_State* L) {
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

	static void Init() {
		DEFMOD(WinAPI);
		DEF(AllocConsole);
		DEF(FreeConsole);
		DEF(GetAsyncKeyState);
		DEF(GetKeyState);
		ENDMOD();
	}
}
