#pragma once

#include "isaac_image.hpp"
#include "pch.h"

#include <imgui/imgui.h>
#include <imsdk/TIMMessageManager.h>
#include <Poco/TaskManager.h>
#include <Poco/Util/JSONConfiguration.h>

#pragma warning(disable: 26495 6387)//禁用警告C26495 C6387: 始终初始化成员变量

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

	struct TaskResult {
		size_t id;
		string result;
	};

	struct TIMRecvNewMsg
	{
		string json_msg_array;
		string user_data;
	};

	struct TIMComm
	{
		int32_t code;
		string desc;
		string json_params;
		string user_data;
	};

	struct _LocalState
	{
		vector<TIMRecvNewMsg> msgs;
		vector<TIMComm> comms;
		vector<TaskResult> tasks;
		Poco::Util::JSONConfiguration _config;
		union { Poco::TaskManager taskManager; };
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
		_LocalState() {}
		~_LocalState() {}
	};

	inline isaac_image::IsaacImage& isaac = *(isaac_image::IsaacImage*)GetModuleHandleA(NULL);
	inline lua_State*& L = isaac.luaEngine->L;
	inline state::_LocalState local;
	inline state::_GlobalState& global = *[] {
		HANDLE hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(_GlobalState), "IsaacSocketSharedMemory");
		return (state::_GlobalState*)MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
		}();
}

#pragma warning(default: 26495 6387)//重新启用警告 C26495 C6387

using state::isaac;
using state::L;
using state::local;
using state::global;