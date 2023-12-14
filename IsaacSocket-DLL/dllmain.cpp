// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "isaac.hpp"
#include "inject.hpp"
#include "state.hpp"

// IsaacSocket类，实现具体功能
struct IsaacSocket
{
	static inline HANDLE hProcess;
	static inline isaac::IsaacImage* isaac;
	static inline state::StateData* stateData;

	// 重新载入lua环境
	static void ReloadLuaWithoutDeleteRoom()
	{
#define _(address,...) auto f_##address = (void(__fastcall*)(__VA_ARGS__))((char*)isaac + address)
		inject::LogPrintf(0, "Lua is resetting!\n");									// 输出日志
		_(0x40AE00, isaac::LuaVM*);													// 卸载lua环境
		f_0x40AE00(isaac->luaVM);
		_(0x3FCB00, isaac::LuaVM*, void*, int);										// 加载lua环境
		f_0x3FCB00(isaac->luaVM, NULL, isaac->luaVM->luaDebug);
		_(0x4702F0, isaac::ModManager&);											// 清除mod列表
		f_0x4702F0(isaac->fileManager->modManager);
		_(0x470B40, isaac::ModManager&);											// 创建mod列表
		f_0x470B40(isaac->fileManager->modManager);
		_(0x46F2B0, isaac::ModManager&);											// 重新加载着色器
		f_0x46F2B0(isaac->fileManager->modManager);
		_(0x4AF200);																// 重新加载精灵和字体
		f_0x4AF200();
		_(0x46DAE0, isaac::ModManager&);											// 重新加载xml
		f_0x46DAE0(isaac->fileManager->modManager);
#undef _
	}

	// 进行一次“额外更新”，即人物更新之类的每秒额外30次更新
	static void SpecialUpdate()
	{
		inject::SpecialUpdate();
	}
	// 进行一次“游戏更新”
	static void GameUpdate()
	{
		inject::GameUpdate(isaac->game);
	}
	// 进行一次“渲染”
	static void Render()
	{
		inject::Render();
	}
	// 进行一次“控制台输出”
	static void ConsoleOutput(const string& text, unsigned int color = 0xFFD3D3D3)
	{
		inject::ConsoleOutput(isaac->game->console, NULL, text, color, 0x96);
	}
	// 进行一次“执行控制台指令”
	static void ExecuteCommand(const string& commandText)
	{
		inject::ExecuteCommand(isaac->game->console, NULL, commandText, 0, 0);
	}
	// 渲染回调，时机在渲染函数的起始位置，只要游戏进程存在就一直触发
	static void OnRender()
	{
		if (stateData->needReload)
		{
			stateData->needReload = false;
			IsaacSocket::ReloadLuaWithoutDeleteRoom();
		}
	}
	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置
	static void OnExecuteCommand(string& str, int unknow, int unknow_point_guess)
	{
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