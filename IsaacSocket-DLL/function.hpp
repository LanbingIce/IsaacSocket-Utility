#pragma once

#include "pch.h"
#include "isaac.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "inject.hpp"

namespace function {

	// 进行一次 “额外更新”，即人物更新之类的每秒额外30次更新
	static void SpecialUpdate()
	{
		inject::SpecialUpdate();
	}

	// 进行一次 “游戏更新”
	static void GameUpdate()
	{
		inject::GameUpdate(local.isaac->game);
	}

	// 进行一次 “控制台输出”
	static void ConsoleOutput(const string& text, uint32_t color = 0xFFD3D3D3)
	{
		inject::ConsoleOutput(local.isaac->game->console, NULL, text, color, 0x96);
	}

	// 进行一次 “执行控制台指令”
	static void ExecuteCommand(const string& commandText)
	{
		inject::ExecuteCommand(local.isaac->game->console, NULL, commandText, 0, 0);
	}

	// 重新载入lua环境
	static void ReloadLuaWithoutDeleteRoom()
	{
		isaac::IsaacImage* isaac = local.isaac;
		// 输出日志
		inject::LogPrintf(0, "Lua is resetting!\n");
		// 卸载lua环境
		FUNC(0x40AE00, void, FASTCALL, isaac::LuaVM*);
		f_0x40AE00(isaac->luaVM);
		// 加载lua环境
		FUNC(0x3FCB00, void, FASTCALL, isaac::LuaVM*, LPCVOID, bool);
		f_0x3FCB00(isaac->luaVM, NULL, isaac->luaVM->luaDebug);
		// 清除mod列表
		FUNC(0x4702F0, void, FASTCALL, isaac::ModManager&);
		f_0x4702F0(isaac->fileManager->modManager);
		// 创建mod列表
		FUNC(0x470B40, void, FASTCALL, isaac::ModManager&);
		f_0x470B40(isaac->fileManager->modManager);
		// 重新加载着色器
		FUNC(0x46F2B0, void, FASTCALL, isaac::ModManager&);
		f_0x46F2B0(isaac->fileManager->modManager);
		// 重新加载精灵和字体
		FUNC(0x4AF200, void, FASTCALL);
		f_0x4AF200();
		// 重新加载xml
		FUNC(0x46DAE0, void, FASTCALL, isaac::ModManager&);
		f_0x46DAE0(isaac->fileManager->modManager);
	}

	// 设置GLFW的接收字符回调，使得直接设置控制台state的方式打开控制台也可以输入字符
	static void SetGLFWCharacter() {
		local.isaac->window->character = (char*)local.isaac + 0x25ECE0;
	}
}
