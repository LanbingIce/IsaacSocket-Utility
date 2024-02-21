#pragma once

#include "lua.hpp"
#include "state.hpp"
#include "module.hpp"
#include "isaac_api.hpp"
#include "memory.hpp"
#include "win_api.hpp"
#include "system_.hpp"
#include "opengl.hpp"
#include "utils.hpp"
#include "imgui.hpp"
#include "isaac_.hpp"

namespace _isaac_socket
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

// 小彭老师专用代码开始
#ifdef __MINGW32__
	static bool LuaReady() { // 小彭老师专用代码开始
		isaac::LuaEngine* luaEngine = local.isaac->luaEngine;
		if (!luaEngine) {
			return false;
		}
		lua_State* L = luaEngine->L;
		if (!L) {
			return false;
		}
		int top = local.lua.lua_gettop(L);
		local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
		bool ok = !local.lua.lua_isnoneornil(L, -1);
        if (ok) {
            local.lua.lua_pushstring(L, "IsaacSocket");
            local.lua.lua_gettable(L, -2);
            ok = !local.lua.lua_isnoneornil(L, -1);
            if (ok) {
                local.lua.lua_setglobal(L, "IsaacSocket");
            }
        }
		local.lua.lua_settop(L, top);
		return ok;
	}
#endif
// 小彭老师专用代码结束

	static void Init() {
		isaac_api::Init();
		memory::Init();
		win_api::Init();
		system_::Init();
		opengl::Init();
		imgui::Init();
		isaac_::Init();

		lua_State* L = local.isaac->luaEngine->L;
		int top = local.lua.lua_gettop(L);
		local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
		local.lua.lua_pushstring(L, "version");
		local.lua.lua_pushstring(L, global->version);
		local.lua.lua_settable(L, -3);

		MODULE_FUNC(Disconnect);

		local.lua.lua_settop(L, top);

		//_cprintf("IsaacSocket initialized\n");
	}
}
