#pragma once

#include "lua.hpp"
#include "pch.h"
#include <imgui/imgui.h>

namespace isaac { struct IsaacImage; }

namespace state {
#pragma warning(disable: 26495)//禁用警告C26495: 始终初始化成员变量
	enum ConnectionState
	{
		DISCONNECTED = 0,
		CONNECTING = 1,
		CONNECTED = 2
	};

	enum MenuBarDisplayMode
	{
		NEVER,
		TAB_HOLD,
		ALWAYS
	};

	enum ImGuiStyleColor
	{
		CLASSIC,
		LIGHT,
		DARK
	};

	struct _GlobalState
	{
		ConnectionState connectionState = DISCONNECTED;
		const char version[8]{};
	};

	struct _LocalState
	{
		struct
		{
			LPCVOID PreSwapBuffers;
			LPCVOID OnExecuteCommand;
			LPCVOID OnConsoleOutput;
			LPCVOID PreWndProc;
		} callbacks;
		HWND hWnd;
		bool initialized = false;
		bool needReload = false;
		char charsInputBuffer[3];
		isaac::IsaacImage* isaac;
		lua::Lua lua;
		uint32_t MTRandomLockedValue = 0;
		HMODULE hOpenGL;
		ImFont* font16;
		bool allocConsole = false;
		MenuBarDisplayMode menuBarDisplayMode = NEVER;
		ImGuiStyleColor styleColor = CLASSIC;
		const string configName = utils::GetDataFilePath("config.json");
		const string iniFileName = utils::GetDataFilePath("imgui.ini");
		const string logFileName = utils::GetDataFilePath("imgui_log.txt");
		struct
		{
			bool ShowDemoWindow = false;
			bool ShowAboutWindow = false;
			bool ShowDebugLogWindow = false;
			bool ShowUserGuide = false;
			bool ShowISAbout= false;
		}imgui;
	};

	inline state::_GlobalState* global;
	inline state::_LocalState local;
#pragma warning(default: 26495)//重新启用警告	C26495
}

using state::global;
using state::local;
