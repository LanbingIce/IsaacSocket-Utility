#pragma once
#include "pch.h"
#include "isaac_image.hpp"

namespace inject {
	void LogPrintf(int level, const char* format, ...);
	void FASTCALL ExecuteCommand(const isaac_image::Console& console, LPCVOID, std::string& text, int unknow, LPCVOID unknow_point_guess);
	void FASTCALL ConsoleOutput(const isaac_image::Console& console, LPCVOID, std::string& text, uint32_t color, int type_guess);
	LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Inject();
}
