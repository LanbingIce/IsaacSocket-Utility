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
		isaac.game->console.state += isaac.game->console.state < 0 ? 5 : 0;
		isaac.game->pauseMenu.state = std::abs(isaac.game->pauseMenu.state);
		VAR_WRITE(isaac.FrameInterval, 1.0 / 60);
		DO_STRING("IsaacSocket = nil");
		local.connectionState = state::DISCONNECTED;
		return 0;
	}

	static void _InitLua() {
		RegisterModule::InitAllModules();

		lua_State* L = isaac.luaEngine->L;
		int top = lua_gettop(L);
		lua_getglobal(L, "_ISAAC_SOCKET");

		MODULE_FUNC(Connect);
		MODULE_FUNC(Disconnect);

		std::ostringstream oss;
		oss << "_ISAAC_SOCKET.version=\"" << global.version << "\" _ISAAC_SOCKET.TaskContinuation={}";
		DO_STRING(oss.str().c_str());

		lua_settop(L, top);
	}

	static bool TryInitLua() {
		lua_State* L = isaac.luaEngine->L;
		int top = lua_gettop(L);
		bool result = false;
		if (lua_getglobal(L, "_ISAAC_SOCKET") == LUA_TTABLE)
		{
			lua_pushstring(L, "Connect");
			lua_gettable(L, -2);
			if (!lua_iscfunction(L, -1))
			{
				_InitLua();
			}
			result = true;
		}
		lua_settop(L, top);
		return result;
	}
}
