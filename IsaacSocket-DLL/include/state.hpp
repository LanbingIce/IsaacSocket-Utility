#pragma once

#include "lua.hpp"
#include "pch.h"
#include "handle.hpp"

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
		std::chrono::system_clock::time_point lastTime;
		size_t frameCounter;
		size_t fps;
	};

	inline state::_GlobalState* global;
	inline state::_LocalState local;
}

using state::global;
using state::local;
