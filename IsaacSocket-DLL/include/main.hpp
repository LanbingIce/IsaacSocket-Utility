#pragma once

#include "pch.h"
#include "lua.hpp"
#include "state.hpp"
#include "function_.hpp"
#include "inject.hpp"
#include "callback.hpp"

namespace main {
	// 初始化，共享内存和注入
	static void Main() {
		setlocale(LC_ALL, ".UTF8");

		local.callbacks = {
			(LPCVOID)callback::PreSwapBuffers,
			(LPCVOID)callback::OnExecuteCommand,
			(LPCVOID)callback::OnConsoleOutput,
			(LPCVOID)callback::PreWndProc,
			callback::TIMRecvNewMsgCallback,
			callback::TIMCommCallback,
		};

		inject::Inject();
	}
}
