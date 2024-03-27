#pragma once

#include "pch.h"
#include "isaac_image.hpp"
#include "result.hpp"

#include <imsdk/TIMMessageManager.h>
#include <Poco/Util/JSONConfiguration.h>

#pragma warning(disable: 26495)//禁用警告C26495: 始终初始化成员变量

namespace state {
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
		vector<result::TIMRecvNewMsg> msgs;
		vector<result::TIMComm> comms;
		vector<result::TaskResult> tasks;
		Poco::Util::JSONConfiguration _config;
		std::mutex mutex;
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
		uint32_t MTRandomLockedValue = 0;
		bool allocConsole = false;
	};

	extern isaac_image::IsaacImage& isaac;
	extern lua_State*& L;
	extern state::_LocalState local;
	extern state::_GlobalState& global;
}

#pragma warning(default: 26495)//重新启用警告 C26495

using state::isaac;
using state::L;
using state::local;
using state::global;