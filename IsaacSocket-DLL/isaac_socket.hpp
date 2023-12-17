#pragma once

#include "pch.h"
#include "lua.hpp"
#include "state.hpp"
#include "function.hpp"
#include "inject.hpp"
#include "callback.hpp"

namespace isaac_socket{

	static HANDLE hProcess;
	static isaac::IsaacImage* isaac;
	static state::StateData* stateData;
	static lua::Lua* lua;

	// 初始化，共享内存和注入
	static void Init(){
		HANDLE hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(state::StateData), "IsaacSocketSharedMemory");
		if (hMapFile)
		{
			hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
			lua = new lua::Lua{ GetModuleHandleA("Lua5.3.3r.dll") };
			stateData = (state::StateData*)MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
			isaac = (isaac::IsaacImage*)GetModuleHandleA(NULL);
			function::Init(isaac);
			callback::Init(stateData, isaac, hProcess, lua);
			inject::Init(hProcess, isaac, callback::GetCallbacks());
			function::SetGLFWCharacter();
		}
	}
}
