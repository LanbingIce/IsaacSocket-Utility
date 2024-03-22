#pragma once

#include "lua.hpp"
#include "pch.h"
#include <imgui/imgui.h>
#include <Poco/TaskManager.h>

namespace isaac { struct IsaacImage; }

namespace state {
#pragma warning(disable: 26495)//禁用警告C26495: 始终初始化成员变量
	enum ConnectionState
	{
		INIT,
		RELOAD_LUA,
		DISCONNECTED,
		CONNECTED
	};

	enum ReloadLuaState
	{
		EXIT,
		SWITCH_PAGE,
		RELOAD
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
		const char version[8]{};
	};

	struct _LocalState
	{
		std::unordered_map<size_t, string> map;
		union { Poco::TaskManager taskManager; };
		std::mutex responsesMutex;
		ConnectionState connectionState = INIT;
		ReloadLuaState reloadLuaState;
		bool isRepentogon = GetModuleHandleA("Lua5.4.dll");
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
		isaac::IsaacImage* isaac;
		lua::Lua lua;
		uint32_t MTRandomLockedValue = 0;
		bool allocConsole = false;
		string currentPath = "C:\\Windows\\Fonts";
		struct
		{
			bool ShowDemoWindow = false;
			bool ShowAboutWindow = false;
			bool ShowDebugLogWindow = false;
			bool ShowUserGuide = false;
			bool ShowISAbout = false;
		}imgui;
		_LocalState() {}
		~_LocalState() {}
	};

	inline state::_GlobalState* global;
	inline state::_LocalState local;
#pragma warning(default: 26495)//重新启用警告	C26495
}

using state::global;
using state::local;
