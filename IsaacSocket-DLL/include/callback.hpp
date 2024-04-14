#pragma once

#include "pch.h"
#include "isaac_image.hpp"
#include <imgui/imgui.h>

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace callback {

	// SwapBuffers之前，只要游戏进程存在就一直触发，返回1则取消此次交换
	int PreSwapBuffers(const HDC hdc);

	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置，返回1则取消此次指令
	int OnExecuteCommand(const isaac_image::Console& console, std::string& text, const int unknow, const LPCVOID unknow_point_guess);

	// 控制台输出回调，时机在控制台输出函数的起始位置，返回1则取消此次输出
	int OnConsoleOutput(const isaac_image::Console& console, std::string& text, const uint32_t color, const int type_guess);

	// 窗口消息回调，返回1则拦截此次消息
	int PreWndProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam);
}