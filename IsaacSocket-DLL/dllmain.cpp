// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "isaac.hpp"
#include "inject.hpp"
#include "state.hpp"
#include "function.hpp"
#include "lua.hpp"
#include "isaac_api.hpp"

// IsaacSocket类，实现具体功能
struct IsaacSocket
{
	static inline HANDLE hProcess;
	static inline isaac::IsaacImage* isaac;
	static inline state::StateData* stateData;
	static inline lua::Lua* lua;

	// 渲染回调，时机在渲染函数的起始位置，只要游戏进程存在就一直触发
	static void OnRender()
	{
		if (stateData->needReload)
		{
			stateData->needReload = false;
			function::ReloadLuaWithoutDeleteRoom();
		}
	}
	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置
	static void OnExecuteCommand(string& str, int unknow, int unknow_point_guess)
	{
		if (str == "test")
		{
			//function::ExecuteCommand("g k1");
			//function::ConsoleOutput("test");
		}
		if (str == "lualua")
		{
			stateData->needReload = true;
		}
		if (str == "ac")
		{
			AllocConsole();
		}
		if (str == "fc")
		{
			FreeConsole();
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

	// MT随机回调
	static uint32_t __fastcall OnMTRandom(uint32_t num)
	{
		return num;
	}

	// 控制台输出回调，时机在控制台输出函数的起始位置
	static void OnConsoleOutput(string& str, int color, int type)
	{
		//utils::cw(str + " " + to_string(type));
	}
};

// 初始化，共享内存和注入
static void Init()
{
	HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, L"IsaacSocketSharedMemory");
	if (hMapFile)
	{
		IsaacSocket::hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
		IsaacSocket::stateData = (state::StateData*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 1024);
		IsaacSocket::isaac = (isaac::IsaacImage*)GetModuleHandle(NULL);
		inject::Callbacks callbacks =
		{
			IsaacSocket::OnRender,
			IsaacSocket::OnGameUpdate,
			IsaacSocket::OnSpecialUpdate,
			IsaacSocket::OnExecuteCommand,
			IsaacSocket::OnConsoleOutput,
			IsaacSocket::OnMTRandom,
		};
		inject::Init(IsaacSocket::hProcess, IsaacSocket::isaac, callbacks);
		function::Init(IsaacSocket::isaac);
		IsaacSocket::lua = new lua::Lua{ GetModuleHandleA("Lua5.3.3r.dll") };
		isaac_api::Init(IsaacSocket::isaac, IsaacSocket:: lua, IsaacSocket:: stateData);
	}
}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Init();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}