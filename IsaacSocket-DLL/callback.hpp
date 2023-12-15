#pragma once

#include "pch.h"
#include "state.hpp"
#include "isaac.hpp"
#include "lua.hpp"
#include "utils.hpp"
#include "isaac_api.hpp"
#include "memory.hpp"
#include "function.hpp"

using utils::cw;

namespace callback {

	state::StateData* stateData;
	isaac::IsaacImage* isaac;
	lua::Lua* lua;
	HANDLE hProcess;

	static void Init(state::StateData* stateData, isaac::IsaacImage* isaac, HANDLE hProcess, lua::Lua* lua) {
		callback::stateData = stateData;
		callback::isaac = isaac;
		callback::hProcess = hProcess;
		callback::lua = lua;
	}

	// 渲染回调，时机在渲染函数的起始位置，只要游戏进程存在就一直触发
	static void OnRender()
	{
		if (stateData->state == state::ON_CONNECTED)
		{
			stateData->state = state::NORMAL;
			isaac_api::Init(isaac, lua, stateData);
			memory::Init(hProcess, isaac, lua);
		}

		if (stateData->needReload)
		{
			stateData->needReload = false;
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
			stateData->needReload = true;
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
				SendMessageA(hwnd, WM_CLOSE, 0, 0);
			}
		}
	}

	// 控制台输出回调，时机在控制台输出函数的起始位置
	static void OnConsoleOutput(const string& text, uint32_t color, int32_t type)
	{

	}

	// MT随机回调
	static uint32_t __fastcall OnMTRandom(uint32_t num)
	{
		num = stateData->lockedMTRandomValue ? stateData->lockedMTRandomValue : num;
		return num;
	}

	static inject::Callbacks GetCallbacks() {
		return{
			OnRender,
			OnGameUpdate,
			OnSpecialUpdate,
			OnExecuteCommand,
			OnConsoleOutput,
			OnMTRandom
		};
	}
}
