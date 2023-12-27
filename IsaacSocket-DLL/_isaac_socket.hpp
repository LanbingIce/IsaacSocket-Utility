#pragma once

#include "lua.hpp"
#include "state.hpp"
#include "isaac_api.hpp"
#include "memory.hpp"
#include "win_api.hpp"
#include "system_.hpp"
#include "opengl.hpp"

namespace _isaac_socket
{
	static int Disconnect(lua_State* L) {
		global->connectionState = state::DISCONNECTED;
		local.MTRandomLockedValue = 0;
		local.needReload = false;
		local.isaac->game->console.state += local.isaac->game->console.state < 0 ? 5 : 0;
		local.isaac->game->pauseMenu.state = std::abs(local.isaac->game->pauseMenu.state);
		return 0;
	}

	static void Init() {

		isaac_api::Init();
		memory::Init();
		win_api::Init();
		system_::Init();
		opengl::Init();

		lua_State* L = local.isaac->luaVM->L;
		size_t top = local.lua->lua_gettop(L);

		local.lua->lua_getglobal(L, "_ISAAC_SOCKET");

#define _(name) local.lua->lua_pushstring(L, #name);local.lua->lua_pushcfunction(L, name); local.lua->lua_settable(L, -3)

		_(Disconnect);

#undef _

		local.lua->lua_settop(L, top);

	}
}
