#pragma once

#include "pch.h"
#include "isaac_image.hpp"
#include "result.hpp"

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

    struct Callbacks
    {
        LPCVOID PreSwapBuffers;
        LPCVOID OnExecuteCommand;
        LPCVOID OnConsoleOutput;
        LPCVOID PreWndProc;
    };

    struct _GlobalState
    {
        const char version[8]{};
    };

    struct _LocalState
    {
        bool isRepentogon = (bool)GetModuleHandleA("Lua5.4.dll");
        bool allocConsole = false;
        ConnectionState connectionState = INIT;
        ReloadLuaState reloadLuaState = EXIT;
        HWND hWnd = 0;
        uint32_t MTRandomLockedValue = 0;
    };

    extern Callbacks callbacks;
    extern isaac_image::IsaacImage& isaac;
    extern lua_State*& L;
    extern state::_LocalState local;
    extern state::_GlobalState& global;
}

#pragma warning(default: 26495)//重新启用警告 C26495

using state::callbacks;
using state::isaac;
using state::L;
using state::local;
using state::global;