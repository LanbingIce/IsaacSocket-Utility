// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "REPENTOGON/include/IsaacRepentance.h"
#include "REPENTOGON/include/HookSystem.h"

struct Callbacks
{
    LPCVOID OnRender;
    LPCVOID OnGameUpdate;
    LPCVOID OnSpecialUpdate;
    LPCVOID OnExecuteCommand;
    LPCVOID OnConsoleOutput;
    LPCVOID OnWindowMessage;
} *localState;

extern "C" __declspec(dllexport) bool HookCallbacks(Callbacks * state) {
    localState = state;
    return true;
}

HOOK_METHOD(Game, Render, () -> void) {
    auto s = localState;
    if (s) {
        ((void(*)())(s->OnRender))();
    }
    super();
}

HOOK_METHOD(Game, Update, ()->void) {
    auto s = localState;
    if (s) {
        ((void(*)())(s->OnGameUpdate))();
    }
    super();
}

/* TODO: more HOOK_METHOD */

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

