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

	static void Init() {
        DEFMOD(WinAPI);
		DEF(AllocConsole);
		DEF(FreeConsole);
        ENDMOD();
	}
}
