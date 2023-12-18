#pragma once

#include "pch.h"
#include "state.hpp"
#include "isaac.hpp"
#include "lua.hpp"
#include "utils.hpp"
#include "isaac_api.hpp"
#include "memory.hpp"
#include "win_api.hpp"
#include "system_.hpp"
#include "function.hpp"
#include "opengl.hpp"

using utils::cw;

namespace callback {

	// 渲染回调，时机在渲染函数的起始位置，只要游戏进程存在就一直触发
	static void OnRender()
	{
		if (global->connectionState == state::CONNECTING)
		{
			if (!local.initialized)
			{
				gladLoadGL();
				function::SetGLFWCharacter();
				local.initialized = true;
			}
			global->connectionState = state::CONNECTED;
			isaac_api::Init();
			memory::Init();
			win_api::Init();
			system_::Init();
			opengl::Init();
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

	}

	// 游戏更新回调，时机在游戏更新函数的起始位置
	static void OnGameUpdate()
	{

	}

	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置
	static void OnExecuteCommand(const string& text, int unknow, LPCVOID unknow_point_guess)
	{
		if (text == "test")
		{
			//function::ExecuteCommand("g k1");
			//function::ConsoleOutput("test");
		}

		if (text == "lualua")
		{
			local.needReload = true;
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

	}


	// 收到键盘输入，返回true则拦截此次消息
	static bool OnCharInput(const char* text)
	{
		lua_State* L = local.isaac->luaVM->L;
		size_t top = local.lua->lua_gettop(L);

		local.lua->lua_getglobal(L, "Isaac");
		local.lua->lua_pushstring(L, "GetCallbacks");
		local.lua->lua_gettable(L, -2);
		local.lua->lua_pushstring(L, "ISAAC_SOCKET_ON_CHAR_INPUT");
		local.lua->lua_pcall(L, 1, 1, 0);
		bool result = false;
		local.lua->lua_pushnil(L);  // 将nil推入栈顶，准备开始遍历
		while (local.lua->lua_next(L, -2) != 0) {
			local.lua->lua_pushstring(L, "Function");
			local.lua->lua_gettable(L, -2);
			local.lua->lua_pushstring(L, "Mod");
			local.lua->lua_gettable(L, -3);
			local.lua->lua_pushstring(L, text);
			local.lua->lua_pcall(L, 2, 1, 0);
			//如果返回值不是nil，则返回true，拦截此次消息
			if (!local.lua->lua_isnil(L, -1))
			{
				result = true;
				break;
			}
			local.lua->lua_pop(L, 2);
		}
		local.lua->lua_settop(L, top);
		return result;
	}

	// 窗口消息回调，返回0则拦截此次消息
	static LRESULT OnWindowMessage(LPCVOID _, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		int result = 1;
		switch (uMsg)
		{
		case WM_CHAR:
			if (!std::iscntrl(wParam))
			{
				// 使用构造函数将单个Unicode码转换为字符串
				std::wstring unicode_string = std::wstring(1, wParam);
				const wchar_t* u16 = unicode_string.c_str();
				size_t size = utils::U16ToU8(u16);
				char* u8 = new char[size];
				utils::U16ToU8(u16, u8, size);
				if (OnCharInput(u8))
				{
					result = 0;
				}
				delete[]u8;
			}
		}
		return result;
	}
}
