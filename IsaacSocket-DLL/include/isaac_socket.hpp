#pragma once

#include "lua.hpp"
#include "state.hpp"
#include "module.hpp"

namespace isaac_socket
{
	static int Disconnect(lua_State* L) {
		global->connectionState = state::DISCONNECTED;
		local.MTRandomLockedValue = 0;
		local.needReload = false;
		local.isaac->game->console.state += local.isaac->game->console.state < 0 ? 5 : 0;
		local.isaac->game->pauseMenu.state = std::abs(local.isaac->game->pauseMenu.state);
		VAR_WRITE(local.isaac->FrameInterval, 1.0 / 60);
		return 0;
	}

	static void Init() {
		RegisterModule::InitAllModules();

		lua_State* L = local.isaac->luaEngine->L;
		int top = local.lua.lua_gettop(L);
		local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
		local.lua.lua_pushstring(L, "version");
		local.lua.lua_pushstring(L, global->version);
		local.lua.lua_settable(L, -3);

		MODULE_FUNC(Disconnect);

		local.lua.lua_settop(L, top);
	}
}
