#pragma once

#include "pch.h"
#include "lua.hpp"
#include "state.hpp"
#include "function.hpp"
#include "inject.hpp"
#include "callback.hpp"

namespace main {
	// 初始化，共享内存和注入
	static void Init() {

		HANDLE hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(*global), "IsaacSocketSharedMemory");

		if (!hMapFile)
		{
			return;
		}

		global = (state::_GlobalState*)MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
		local.isaac = (isaac::IsaacImage*)GetModuleHandleA(NULL);
		local.hOpenGL = GetModuleHandleA("opengl32.dll");

		local.callbacks = {
			(LPCVOID)callback::PreSwapBuffers,
			(LPCVOID)callback::OnExecuteCommand,
			(LPCVOID)callback::OnConsoleOutput,
			(LPCVOID)callback::PreWndProc,
		};

		inject::Init();
	}
}
