#pragma once

#include "pch.h"
#include "lua.hpp"
#include "state.hpp"
#include "function.hpp"
#include "inject.hpp"
#include "callback.hpp"

namespace main {
	// 初始化，共享内存和注入
	static void Init(bool useSharedMemory = true) { // true: c# 客户端, false: c++ 客户端

		if (useSharedMemory) {
			HANDLE hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(*global), "IsaacSocketSharedMemory");
			if (!hMapFile) return;

			global = (state::_GlobalState*)MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
		}
		else {
			global = nullptr;//new state::_GlobalState{state::CONNECTING};
		}

		local.useSharedMemory = useSharedMemory;
		local.isaac = (isaac::IsaacImage*)GetModuleHandleA(NULL);
		local.hOpenGL = GetModuleHandleA("opengl32.dll");

		/* if (!local.hProcess) MessageBoxW(NULL, L"以撒进程对象句柄为空！", L"错误", MB_OK); */
		/* if (!local.isaac) MessageBoxW(NULL, L"以撒句柄 local.isaac 为空！", L"错误", MB_OK); */
		/* if (!local.hOpenGL) MessageBoxW(NULL, L"OpenGL 句柄 local.hOpenGL 为空！", L"错误", MB_OK); */

		local.callbacks = {
			(LPCVOID)callback::PreSwapBuffers,
			(LPCVOID)callback::OnExecuteCommand,
			(LPCVOID)callback::OnConsoleOutput,
			(LPCVOID)callback::PreWndProc,
		};
		/* if (!local.isaac) MessageBoxW(NULL, L"以撒句柄 local.isaac 为空1！", L"错误", MB_OK); */

		inject::Init();
	}
}
