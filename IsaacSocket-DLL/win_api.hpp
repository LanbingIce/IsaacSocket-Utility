#pragma once

#include "lua.hpp"

namespace win_api
{
	static lua::Lua* lua;

	static int AllocConsole(lua_State* L) {
		::AllocConsole();
		return 0;
	}

	static int FreeConsole(lua_State* L) {
		::FreeConsole();
		return 0;
	}

	void Init(lua_State* L, lua::Lua* lua) {
		size_t top = lua->lua_gettop(L);
		win_api::lua = lua;

		lua->lua_getglobal(L, "_ISAAC_SOCKET");
		lua->lua_pushstring(L, "IsaacSocket");
		lua->lua_gettable(L, -2);
		lua->lua_pushstring(L, "WinAPI");
		lua->lua_newtable(L);

#define _(name) lua->lua_pushstring(L, #name);lua->lua_pushcfunction(L, name); lua->lua_settable(L, -3)

		_(AllocConsole);
		_(FreeConsole);

#undef _

		lua->lua_settable(L, -3);
		lua->lua_settop(L, top);
	}
}