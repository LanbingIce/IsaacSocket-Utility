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
		time_t currentTime;
		time(&currentTime);
		if (currentTime != local.lastTime)
		{
			local.lastTime = currentTime;
			local.fps = local.frameCounter;
			local.frameCounter = 0;
		}
		local.frameCounter++;

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
		}
		else {

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
			static int counter = 0;
			counter++;
			if (counter % 30) {
				if (reloadLibraryMain("IsaacSocket.dll", true)) {
					_cprintf("auto reloaded dll\n");
					return;
				}
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

	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置，返回true则拦截此次消息
	static bool OnExecuteCommand(string& text, int unknow, LPCVOID unknow_point_guess)
	{
		if (!local.initialized) return true;
		if (local.useSharedMemory && global->connectionState != state::CONNECTED)
		{
			return true;
		}

		_MOD_CALLBACK(ISMC_PRE_EXECUTE_CMD);
		local.lua.lua_pushlstring(L, text.c_str(), text.size());
		local.lua.lua_pcall(L, 2, 1, 0);
		if (local.lua.lua_isstring(L, -1))
		{
			text = local.lua.lua_tolstring(L, -1, nullptr);
		}
		else _MOD_CALLBACK_END();

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
			//local.needReloadDll = true;
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
		return true;
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

	// 窗口消息回调，返回0则拦截此次消息
	static LRESULT OnWindowMessage(LPCVOID _, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (!local.initialized) return 1;
		if (local.useSharedMemory && global->connectionState != state::CONNECTED)
		{
			return 1;
		}
		char* buffer = local.charsInputBuffer;
		switch (uMsg)
		{
		case WM_CHAR:
			if (std::iscntrl(wParam))
			{
				break;
			}
			if (buffer[0] < 0)
			{
				buffer[1] = wParam;
				size_t len = utils::AnsiToU16(buffer);
				vector<wchar_t> u16(len);
				utils::AnsiToU16(buffer, u16.data(), len);
				len = utils::U16ToU8(u16.data());
				vector<char> u8(len);
				utils::U16ToU8(u16.data(), u8.data(), len);
				buffer[0] = 0;
				buffer[1] = 0;
				{
					//兼容旧版名称，下个版本删除
					MOD_CALLBACK(ISAAC_SOCKET_ON_CHAR_INPUT, string, u8.data());
				}
				{
					MOD_CALLBACK(ISMC_PRE_CHAR_INPUT, string, u8.data());
				}
			}
			else
			{
				buffer[0] = wParam;
				if (buffer[0] >= 0)
				{
					{
						//兼容旧版名称，下个版本删除
						MOD_CALLBACK(ISAAC_SOCKET_ON_CHAR_INPUT, string, buffer);
					}
					{
						MOD_CALLBACK(ISMC_PRE_CHAR_INPUT, string, buffer);
					}
				}
			}
			break;
		case WM_KEYDOWN:
		{
			//兼容旧版名称，下个版本删除
			MOD_CALLBACK(ISAAC_SOCKET_ON_KEY_DOWN, integer, wParam);
		}
		{
			MOD_CALLBACK(ISMC_PRE_KEY_DOWN, integer, wParam);
		}
		break;
		}
		return 1;
	}
}
