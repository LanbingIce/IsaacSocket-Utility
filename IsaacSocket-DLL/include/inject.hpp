#pragma once
#include "pch.h"
#include "isaac.hpp"

namespace inject {
	void LogPrintf(int level, const char* format, ...);
	void FASTCALL ExecuteCommand(isaac::Console& console, LPCVOID, string& text, int unknow, LPCVOID unknow_point_guess);
	void FASTCALL ConsoleOutput(isaac::Console& console, LPCVOID, string& text, uint32_t color, int type_guess);
	LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Init();
}
