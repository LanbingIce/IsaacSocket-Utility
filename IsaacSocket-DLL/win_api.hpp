#pragma once

#include "lua.hpp"

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
		lua_State* L = local.isaac->luaVM->L;
		size_t top = local.lua.lua_gettop(L);

		local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
		local.lua.lua_pushstring(L, "IsaacSocket");
		local.lua.lua_gettable(L, -2);
		local.lua.lua_pushstring(L, "WinAPI");
		local.lua.lua_newtable(L);

#define _(name) local.lua.lua_pushstring(L, #name);local.lua.lua_pushcfunction(L, name); local.lua.lua_settable(L, -3)

		_(AllocConsole);
		_(FreeConsole);

#undef _

		local.lua.lua_settable(L, -3);
		local.lua.lua_settop(L, top);
	}
}
