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
			LPCVOID OnRender;
			LPCVOID OnGameUpdate;
			LPCVOID OnSpecialUpdate;
			LPCVOID OnExecuteCommand;
			LPCVOID OnConsoleOutput;
			LPCVOID OnWindowMessage;
		} callbacks;

		bool initialized = false;
		bool needReload = false;
		bool needReloadDll = false;
		bool useSharedMemory;
		char charsInputBuffer[3];
		isaac::IsaacImage* isaac;
		lua::Lua lua;
		uint32_t MTRandomLockedValue = 0;
		HMODULE hOpenGL;
	};

	inline state::_GlobalState* global;
	inline state::_LocalState local;
}

using state::global;
using state::local;
