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
		local.needReloadDll = false;
		local.isaac->game->console.state += local.isaac->game->console.state < 0 ? 5 : 0;
		local.isaac->game->pauseMenu.state = std::abs(local.isaac->game->pauseMenu.state);
		VAR_WRITE(local.isaac->FrameInterval, 1.0 / 60);
		return 0;
	}

	static int ReloadDLL(lua_State* L) {
		local.needReloadDll = true;
		return 0;
	}

	static bool LuaReady() {
		isaac::LuaEngine* luaEngine = local.isaac->luaEngine;
		if (!luaEngine) {
			return false;
		}
		lua_State* L = luaEngine->L;
		if (!L) {
			return false;
		}
		int top = local.lua.lua_gettop(L);
		local.lua.lua_getglobal(L, "REPENTANCE");
		bool ok = !local.lua.lua_isnil(L, -1);
		local.lua.lua_settop(L, top);
		return ok;
	}

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

		DEF(Disconnect);
		DEF(ReloadDLL);

		local.lua.lua_settop(L, top);

		//_cprintf("IsaacSocket initialized\n");
	}
}
