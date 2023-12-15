#pragma once

#include "lua.hpp"
#include "utils.hpp"

namespace system_
{
	static lua::Lua* lua;

	//系统控制台输出
	static int ConsoleOutput(lua_State* L) {
		if (GetConsoleWindow())
		{
			ARG(1, string, const char*, text);
			utils::Utf8Cprintf(text);
		}
		return 0;
	}

	void Init(lua_State* L, lua::Lua* lua) {
		size_t top = lua->lua_gettop(L);
		system_::lua = lua;

		lua->lua_getglobal(L, "_ISAAC_SOCKET");
		lua->lua_pushstring(L, "IsaacSocket");
		lua->lua_gettable(L, -2);
		lua->lua_pushstring(L, "System");
		lua->lua_newtable(L);

#define _(name) lua->lua_pushstring(L, #name);lua->lua_pushcfunction(L, name); lua->lua_settable(L, -3)

		_(ConsoleOutput);

#undef _

		lua->lua_settable(L, -3);
		lua->lua_settop(L, top);
	}
};