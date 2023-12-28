﻿// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "main.hpp"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        MessageBoxW(NULL, L"IsaacSocket 注入成功", L"喜报", MB_OK);
		main::Init();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
