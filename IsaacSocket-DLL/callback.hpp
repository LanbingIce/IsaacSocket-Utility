#pragma once

#include "pch.h"
#include "state.hpp"
#include "utils.hpp"
#include "function.hpp"
#include "_isaac_socket.hpp"
#include "reload.hpp"

using utils::cw;

namespace callback {

	// 渲染回调，时机在渲染函数的起始位置，只要游戏进程存在就一直触发
	static void OnRender()
	{
        if (local.useSharedMemory) {
            if (global->connectionState == state::DISCONNECTED)
            {
                return;
            }
            if (global->connectionState == state::CONNECTING)
            {
                if (!local.initialized)
                {
                    gladLoadGL();
                    function::SetGLFWCharacter();
                    local.initialized = true;
                }
                global->connectionState = state::CONNECTED;
                _isaac_socket::Init();
            }
        } else {
        
                if (!local.initialized && _isaac_socket::LuaReady())
                {
                    gladLoadGL();
                    function::SetGLFWCharacter();
                    _isaac_socket::Init();
                    local.initialized = true;
                }
        }
#ifdef __MINGW32__
		if (getenv("IsaacSocketAutoReloadDll")) {
            if (reloadLibraryMain("IsaacSocket.dll", true)) {
                _cprintf("auto reloaded dll\n");
                return;
            }
        }
#endif
        if (local.needReloadDll)
		{
            reloadLibraryMain("IsaacSocket.dll");
			local.needReloadDll = false;
            return;
		}

		if (local.needReload)
		{
			local.needReload = false;
			function::ReloadLuaWithoutDeleteRoom();
		}

	}

	// 额外更新回调，时机在额外更新函数的起始位置
	static void OnSpecialUpdate()
	{
		if (!local.initialized) return;
		if (local.useSharedMemory && global->connectionState != state::CONNECTED)
		{
			return;
		}
	}

	// 游戏更新回调，时机在游戏更新函数的起始位置
	static void OnGameUpdate()
	{
		if (!local.initialized) return;
		if (local.useSharedMemory && global->connectionState != state::CONNECTED)
		{
			return;
		}
	}

	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置
	static void OnExecuteCommand(const string& text, int unknow, LPCVOID unknow_point_guess)
	{
		if (!local.initialized) return;
		if (local.useSharedMemory && global->connectionState != state::CONNECTED)
		{
			return;
		}

		if (text == "test")
		{
			//function::ExecuteCommand("g k1");
			//function::ConsoleOutput("test");
		}

		if (text == "lualua")
		{
			local.needReload = true;
		}

		if (text == "luadll")
		{
			local.needReloadDll = true;
		}

		if (text == "ac")
		{
			AllocConsole();
			HWND hwnd = FindWindowA("GLFW30", "Binding of Isaac: Repentance");
			SetForegroundWindow(hwnd);
		}

		if (text == "fc")
		{
			HWND hwnd = GetConsoleWindow();
			if (hwnd)
			{
				FreeConsole();
				PostMessageA(hwnd, WM_CLOSE, 0, 0);
			}
		}
	}

	// 控制台输出回调，时机在控制台输出函数的起始位置
	static void OnConsoleOutput(const string& text, uint32_t color, int32_t type)
	{
		if (!local.initialized) return;
		if (local.useSharedMemory && global->connectionState != state::CONNECTED)
		{
			return;
		}
	}


	// 收到键盘输入，返回true则拦截此次消息
	static bool OnCharInput(const char* text)
	{
		lua_State* L = local.isaac->luaVM->L;
		size_t top = local.lua.lua_gettop(L);

		local.lua.lua_getglobal(L, "Isaac");
		local.lua.lua_pushstring(L, "GetCallbacks");
		local.lua.lua_gettable(L, -2);
		local.lua.lua_pushstring(L, "ISAAC_SOCKET_ON_CHAR_INPUT");
		local.lua.lua_pcall(L, 1, 1, 0);
		bool result = false;
		local.lua.lua_pushnil(L);  // 将nil推入栈顶，准备开始遍历
		while (local.lua.lua_next(L, -2) != 0) {
			local.lua.lua_pushstring(L, "Function");
			local.lua.lua_gettable(L, -2);
			local.lua.lua_pushstring(L, "Mod");
			local.lua.lua_gettable(L, -3);
			local.lua.lua_pushstring(L, text);
			local.lua.lua_pcall(L, 2, 1, 0);
			//如果返回值不是nil，则返回true，拦截此次消息
			if (!local.lua.lua_isnil(L, -1))
			{
				result = true;
				break;
			}
			local.lua.lua_pop(L, 2);
		}
		local.lua.lua_settop(L, top);
		return result;
	}

	// 窗口消息回调，返回0则拦截此次消息
	static LRESULT OnWindowMessage(LPCVOID _, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (!local.initialized) return 1;
		if (local.useSharedMemory && global->connectionState != state::CONNECTED)
		{
			return 1;
		}
		int result = 1;
        char *buffer = state::charsBuffer;
		switch (uMsg)
		{
		case WM_CHAR:
			if (!std::iscntrl(wParam))
			{
				if (buffer[0] < 0)
				{
					buffer[1] = wParam;
					size_t len = utils::AnsiToU16(buffer);
					vector<wchar_t> u16(len);
					utils::AnsiToU16(buffer, u16.data(), len);
					len = utils::U16ToU8(u16.data());
					vector<char> u8(len);
					utils::U16ToU8(u16.data(), u8.data(), len);
					if (OnCharInput(u8.data()))
					{
						result = 0;
					}
					buffer[0] = 0;
					buffer[1] = 0;
				}
				else
				{
					buffer[0] = wParam;
					if (buffer[0] >= 0 && OnCharInput(buffer))
					{
						result = 0;
					}
				}
			}
		}
		return result;
	}
}
