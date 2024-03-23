#pragma once

#include "lua.hpp"
#include "state.hpp"
#include "module.hpp"
#include <imsdk/TIMManager.h>

namespace isaac_socket
{
	static int Connect(lua_State* L) {
		local.connectionState = state::CONNECTED;
		DO_STRING("IsaacSocket = _ISAAC_SOCKET.IsaacSocket");

		FAST_MOD_CALLBACK_BEGIN(ISMC_POST_OPEN);
		FAST_MOD_CALLBACK_END();
		return 0;
	}

	static int Disconnect(lua_State* L) {
		FAST_MOD_CALLBACK_BEGIN(ISMC_PRE_CLOSE);
		FAST_MOD_CALLBACK_END();
		TIMUninit();
		local.MTRandomLockedValue = 0;
		local.isaac->game->console.state += local.isaac->game->console.state < 0 ? 5 : 0;
		local.isaac->game->pauseMenu.state = std::abs(local.isaac->game->pauseMenu.state);
		VAR_WRITE(local.isaac->FrameInterval, 1.0 / 60);
		DO_STRING("IsaacSocket = nil");
		local.connectionState = state::DISCONNECTED;
		return 0;
	}

	static void _Init() {
		RegisterModule::InitAllModules();

		lua_State* L = local.isaac->luaEngine->L;
		int top = local.lua.lua_gettop(L);
		local.lua.lua_getglobal(L, "_ISAAC_SOCKET");

		MODULE_FUNC(Connect);
		MODULE_FUNC(Disconnect);

		std::ostringstream oss;
		oss << "_ISAAC_SOCKET.version=\"" << global->version << "\" _ISAAC_SOCKET.TaskContinuation={}";
		DO_STRING(oss.str().c_str());

		local.lua.lua_settop(L, top);
	}

	static bool CheckInit() {
		lua_State* L = local.isaac->luaEngine->L;
		int top = local.lua.lua_gettop(L);
		bool result = false;
		if (local.lua.lua_getglobal(L, "_ISAAC_SOCKET") == LUA_TTABLE)
		{
			local.lua.lua_pushstring(L, "Connect");
			local.lua.lua_gettable(L, -2);
			if (!local.lua.lua_iscfunction(L, -1))
			{
				_Init();
			}
			result = true;
		}
		local.lua.lua_settop(L, top);
		return result;
	}
}
