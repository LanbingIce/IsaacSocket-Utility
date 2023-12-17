#pragma once

#include "pch.h"
#include "lua.hpp"
#include "state.hpp"
#include "function.hpp"
#include "inject.hpp"
#include "callback.hpp"

namespace isaac_socket {
	// 初始化，共享内存和注入
	static void Init() {
		HANDLE hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(global), "IsaacSocketSharedMemory");
		if (hMapFile)
		{
			global = (state::_GlobalState*)MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);

			local.hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, GetCurrentProcessId());
			local.lua = new lua::Lua{ GetModuleHandleA("Lua5.3.3r.dll") };
			local.isaac = (isaac::IsaacImage*)GetModuleHandleA(NULL);
			local.hOpenGL = GetModuleHandleA("opengl32.dll");

			callbacks = {
					callback::OnRender,
					callback::OnGameUpdate,
					callback::OnSpecialUpdate,
					callback::OnExecuteCommand,
					callback::OnConsoleOutput,
					callback::OnWindowMessage
			};

			inject::Init();
		}
	}
}
