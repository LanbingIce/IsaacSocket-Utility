#pragma once
#include "pch.h"
#include "isaac.hpp"

namespace inject {
	void LogPrintf(int level, const char* format, ...);
	void Render();
	void FASTCALL GameUpdate(isaac::Game* gamePtr);
	void SpecialUpdate();
	void FASTCALL ExecuteCommand(isaac::Console& console, LPCVOID _, const string& text, int unknow, int unknow_point_guess);
	void FASTCALL ConsoleOutput(isaac::Console& console, LPCVOID _, const string& text, uint32_t color, uint32_t type_guess);
	void MTRandom();
	LRESULT WINAPI Wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Init();
}
