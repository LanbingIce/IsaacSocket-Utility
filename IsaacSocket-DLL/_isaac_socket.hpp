#pragma once

#include "lua.hpp"
#include "state.hpp"
#include "module.hpp"
#include "isaac_api.hpp"
#include "memory.hpp"
#include "win_api.hpp"
#include "system_.hpp"
#include "opengl.hpp"

namespace _isaac_socket
{
	static int Disconnect(lua_State* L) {
        if (local.useSharedMemory) global->connectionState = state::DISCONNECTED;
		local.MTRandomLockedValue = 0;
		local.needReload = false;
		local.needReloadDll = false;
		local.isaac->game->console.state += local.isaac->game->console.state < 0 ? 5 : 0;
		local.isaac->game->pauseMenu.state = std::abs(local.isaac->game->pauseMenu.state);
		return 0;
	}

    static int ReloadDLL(lua_State* L) {
		local.needReloadDll = true;
        return 0;
    }

    static bool LuaReady() {
        isaac::LuaVM *luaVM = local.isaac->luaVM;
        if (!luaVM) {
            return false;
        }
        lua_State *L = luaVM->L;
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
        //_cprintf("IsaacSocket initializing...\n");
        /* MessageBoxW(NULL, L"IsaacSocket 正在初始化", L"喜报", MB_OK); */

        if (!local.useSharedMemory) {
            lua_State* L = local.isaac->luaVM->L;
            int top = local.lua.lua_gettop(L);
            // _ISAAC_SOCKET = {}
            local.lua.lua_newtable(L);
            local.lua.lua_setglobal(L, "_ISAAC_SOCKET");
            // _ISAAC_SOCKET.IsaacSocket = {}
            local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
            local.lua.lua_pushstring(L, "IsaacSocket");
            local.lua.lua_newtable(L);
            local.lua.lua_settable(L, -3);
            // IsaacSocket = _ISAAC_SOCKET.IsaacSocket
            local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
            local.lua.lua_pushstring(L, "IsaacSocket");
            local.lua.lua_gettable(L, -2);
            local.lua.lua_setglobal(L, "IsaacSocket");
            local.lua.lua_settop(L, top);
        }

		isaac_api::Init();
		memory::Init();
		win_api::Init();
		system_::Init();
		opengl::Init();

		lua_State* L = local.isaac->luaVM->L;
		int top = local.lua.lua_gettop(L);
		local.lua.lua_getglobal(L, "_ISAAC_SOCKET");

		DEF(Disconnect);
		DEF(ReloadDLL);

		local.lua.lua_settop(L, top);

        //_cprintf("IsaacSocket initialized\n");
	}
}
