#pragma once

#include "lua.hpp"
#include "pch.h"

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
			LPCVOID Render;
			LPCVOID GameUpdate;
			LPCVOID SpecialUpdate;
			LPCVOID ExecuteCommand;
			LPCVOID ConsoleOutput;
			LPCVOID OnWindowMessage;
		} callbacks;

		bool initialized = false;
		bool needReload = false;
        bool useSharedMemory;
		HANDLE hProcess;
		HMODULE hOpenGL;
		isaac::IsaacImage* isaac;
        lua::Lua lua;
		uint32_t MTRandomLockedValue = 0;
	};

	inline state::_GlobalState* global;
	inline state::_LocalState local;
	inline char charsBuffer[3];


}

using state::global;
using state::local;
