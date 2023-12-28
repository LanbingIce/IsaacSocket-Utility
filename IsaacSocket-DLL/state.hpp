#pragma once

#include "pch.h"

namespace lua { struct Lua; }
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
			void (*OnRender)();
			void (*OnGameUpdate)();
			void (*OnSpecialUpdate)();
			void (*OnExecuteCommand)(const string&, int, LPCVOID);
			void (*OnConsoleOutput)(const string&, uint32_t, int32_t);
			LRESULT(*OnWindowMessage)(LPCVOID, HWND, UINT, WPARAM, LPARAM);
		} callbacks;

		bool initialized = false;
		bool needReload = false;
		HANDLE hProcess;
		HMODULE hOpenGL;
		isaac::IsaacImage* isaac;
		lua::Lua lua;
		uint32_t MTRandomLockedValue = 0;
	};

	static state::_GlobalState* global;
	static state::_LocalState local;

}

using state::global;
using state::local;
