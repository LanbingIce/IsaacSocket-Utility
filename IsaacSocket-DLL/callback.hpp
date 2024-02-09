#pragma once

#include "pch.h"
#include "state.hpp"
#include "utils.hpp"
#include "function.hpp"
#include "_isaac_socket.hpp"
#include "reload.hpp"

using utils::cw;

#define CHECK_STATE()if (!local.initialized) return 1;if (local.useSharedMemory && global->connectionState != state::CONNECTED)return 1
namespace callback {

	// SwapBuffers之前，只要游戏进程存在就一直触发
	static int PreSwapBuffers(HDC hdc)
	{
		if (local.useSharedMemory) {
			if (global->connectionState == state::DISCONNECTED)
			{
				return 1;
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
		auto currentTime = std::chrono::system_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - local.lastTime).count() != 0)
		{
			local.lastTime = currentTime;
			local.fps = local.frameCounter;
			local.frameCounter = 0;
		}
		local.frameCounter++;
		if (local.needReloadDll)
		{
			reloadLibraryMain("IsaacSocket.dll");
			local.needReloadDll = false;
			return 1;
		}

		if (local.needReload)
		{
			local.needReload = false;
			function::ReloadLuaWithoutDeleteRoom();
			return 1;
		}

		MOD_CALLBACK_BEGIN(ISMC_PRE_SWAP_BUFFERS);
		MOD_CALLBACK_CALL();
		MOD_CALLBACK_END();

		return 1;
	}

	// 额外更新回调，时机在额外更新函数的起始位置
	static int OnSpecialUpdate()
	{
		CHECK_STATE();
		return 1;
	}

	// 游戏更新回调，时机在游戏更新函数的起始位置
	static int OnGameUpdate()
	{
		CHECK_STATE();
		return 1;
	}

	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置，返回false则取消此次指令
	static int OnExecuteCommand(string& text, int unknow, LPCVOID unknow_point_guess)
	{
		CHECK_STATE();

		MOD_CALLBACK_BEGIN(ISMC_PRE_EXECUTE_CMD);
		MOD_CALLBACK_ARG(lstring, text.c_str(), text.size());
		MOD_CALLBACK_CALL();
		if (local.lua.lua_isstring(L, -1))
		{
			text = local.lua.lua_tolstring(L, -1, nullptr);
		}
		else MOD_CALLBACK_END();

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
		return 1;
	}

	// 控制台输出回调，时机在控制台输出函数的起始位置，返回0则取消此次输出
	static int OnConsoleOutput(string& text, uint32_t color, int32_t type)
	{
		CHECK_STATE();

		MOD_CALLBACK_BEGIN(ISMC_PRE_CONSOLE_OUTPUT);
		MOD_CALLBACK_ARG(lstring, text.c_str(), text.size());
		MOD_CALLBACK_ARG(integer, color);
		MOD_CALLBACK_CALL();

		if (local.lua.lua_isstring(L, -1))
		{
			text = local.lua.lua_tolstring(L, -1, nullptr);
		}
		else MOD_CALLBACK_END();

		return 1;
	}

	// 窗口消息回调，返回0则拦截此次消息
	static int PreWndProc(LPCVOID _, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		CHECK_STATE();
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
				MOD_CALLBACK_BEGIN(ISMC_PRE_CHAR_INPUT);
				MOD_CALLBACK_ARG(string, u8.data());
				MOD_CALLBACK_CALL();
				MOD_CALLBACK_END();
			}
			else
			{
				buffer[0] = wParam;
				if (buffer[0] >= 0)
				{
					MOD_CALLBACK_BEGIN(ISMC_PRE_CHAR_INPUT);
					MOD_CALLBACK_ARG(string, buffer);
					MOD_CALLBACK_CALL();
					MOD_CALLBACK_END();
				}
			}
			break;
		case WM_KEYDOWN:
			MOD_CALLBACK_BEGIN(ISMC_PRE_KEY_DOWN);
			MOD_CALLBACK_ARG(integer, wParam);
			MOD_CALLBACK_CALL();
			MOD_CALLBACK_END();
			break;
		}
		return 1;
	}
}
#undef CHECK_STATE