// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "isaac.hpp"
#include "inject.hpp"
#include "state.hpp"
#include "function.hpp"
#include "lua.hpp"
#include "isaac_api.hpp"
#include "callback.hpp"

// IsaacSocket类，实现具体功能
struct IsaacSocket
{
	static inline HANDLE hProcess;
	static inline isaac::IsaacImage* isaac;
	static inline state::StateData* stateData;
	static inline lua::Lua* lua;
};

// 初始化，共享内存和注入
static void Init()
{
	HANDLE hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(state::StateData), "IsaacSocketSharedMemory");
	if (hMapFile)
	{
		IsaacSocket::hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
		IsaacSocket::stateData = (state::StateData*)MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
		IsaacSocket::isaac = (isaac::IsaacImage*)GetModuleHandleA(NULL);
		inject::Init(IsaacSocket::hProcess, IsaacSocket::isaac, callback::GetCallbacks());
		function::Init(IsaacSocket::isaac);
		IsaacSocket::lua = new lua::Lua{ GetModuleHandleA("Lua5.3.3r.dll") };
		callback::Init(IsaacSocket::stateData, IsaacSocket::isaac, IsaacSocket::hProcess, IsaacSocket::lua);
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