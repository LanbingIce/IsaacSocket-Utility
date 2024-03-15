#pragma once

#include "lua.hpp"
#include "imsdk.hpp"
#include "pch.h"
#include <imgui/imgui.h>

namespace isaac { struct IsaacImage; }

namespace state {
#pragma warning(disable: 26495)//禁用警告C26495: 始终初始化成员变量
	enum ConnectionState
	{
		NEED_INIT,
		NEED_RELOAD_LUA,
		DISCONNECTED,
		CONNECTED
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
		char padding[4];
		const char version[8]{};
	};

	struct _LocalState
	{
		ConnectionState connectionState = NEED_INIT;
		struct
		{
			LPCVOID PreSwapBuffers;
			LPCVOID OnExecuteCommand;
			LPCVOID OnConsoleOutput;
			LPCVOID PreWndProc;
			TIMRecvNewMsgCallback TIMRecvNewMsgCallback;
			TIMCommCallback TIMCommCallback;
		} callbacks;
		HWND hWnd;
		char charsInputBuffer[2];
		isaac::IsaacImage* isaac;
		lua::Lua lua;
		imsdk::ImSDK imsdk;
		uint32_t MTRandomLockedValue = 0;
		HMODULE hOpenGL;
		bool allocConsole = false;
		MenuBarDisplayMode menuBarDisplayMode = NEVER;
		ImGuiStyleColor styleColor = CLASSIC;
		const string configName = utils::GetDataFilePath("config.json");
		const string iniFileName = utils::GetDataFilePath("imgui.ini");
		const string logFileName = utils::GetDataFilePath("imgui_log.txt");
		string currentPath = ".";
		string fontFileName;
		float fontSize;
		struct
		{
			bool ShowDemoWindow = false;
			bool ShowAboutWindow = false;
			bool ShowDebugLogWindow = false;
			bool ShowUserGuide = false;
			bool ShowISAbout = false;
		}imgui;
	};

	inline state::_GlobalState* global;
	inline state::_LocalState local;
#pragma warning(default: 26495)//重新启用警告	C26495
}

using state::global;
using state::local;
