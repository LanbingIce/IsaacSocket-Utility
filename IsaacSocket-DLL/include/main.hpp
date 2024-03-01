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
		setlocale(LC_ALL, ".UTF8");
		HANDLE hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(*global), "IsaacSocketSharedMemory");

		if (!hMapFile)
		{
			return;
		}

		global = (state::_GlobalState*)MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
		local.isaac = (isaac::IsaacImage*)GetModuleHandleA(NULL);
		local.hOpenGL = GetModuleHandleA("opengl32.dll");
		local.styleColor = (state::ImGuiStyleColor)config::GetInt({ "IsaacSocket", "StyleColors" });
		local.menuBarDisplayMode = (state::MenuBarDisplayMode)config::GetInt({ "IsaacSocket",  "MenuBar" });
		local.fontFileName = config::GetString({ "IsaacSocket", "FontFile" });
		local.fontSize = config::GetFloat({ "IsaacSocket", "FontSize" });

		local.callbacks = {
			(LPCVOID)callback::PreSwapBuffers,
			(LPCVOID)callback::OnExecuteCommand,
			(LPCVOID)callback::OnConsoleOutput,
			(LPCVOID)callback::PreWndProc,
			callback::TIMRecvNewMsgCallback,
			callback::TIMCommCallback,
		};

		inject::Init();
	}
}
