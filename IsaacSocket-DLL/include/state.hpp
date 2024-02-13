#pragma once

#include "lua.hpp"
#include "pch.h"
#include "handle.hpp"
#include <imgui/imgui.h>

namespace isaac { struct IsaacImage; }

namespace state {

	enum ConnectionState
	{
		DISCONNECTED = 0,
		CONNECTING = 1,
		CONNECTED = 2
	};

	struct _GlobalState
	{
		ConnectionState connectionState;
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
		bool needReloadDll = false;
		char charsInputBuffer[3];
		isaac::IsaacImage* isaac;
		lua::Lua lua;
		uint32_t MTRandomLockedValue = 0;
		HMODULE hOpenGL;
		ImFont* font;
	};

	inline state::_GlobalState* global;
	inline state::_LocalState local;
}

using state::global;
using state::local;
