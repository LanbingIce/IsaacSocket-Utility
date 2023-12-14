#pragma once

#include "pch.h"
#include "isaac.hpp"
#include "inject.hpp"

namespace function {

	isaac::IsaacImage* isaac;

	static void Init(isaac::IsaacImage* isaac) {
		function::isaac = isaac;
	}

	// 进行一次 “额外更新”，即人物更新之类的每秒额外30次更新
	static void SpecialUpdate()
	{
		inject::SpecialUpdate();
	}

	// 进行一次 “游戏更新”
	static void GameUpdate()
	{
		inject::GameUpdate(isaac->game);
	}

	// 进行一次“渲染”
	static void Render()
	{
		inject::Render();
	}

	// 进行一次 “控制台输出”
	static void ConsoleOutput(const string& text, uint32_t color = 0xFFD3D3D3)
	{
		inject::ConsoleOutput(isaac->game->console, NULL, text, color, 0x96);
	}

	// 进行一次 “执行控制台指令”
	static void ExecuteCommand(const string& commandText)
	{
		inject::ExecuteCommand(isaac->game->console, NULL, commandText, 0, 0);
	}

	// 重新载入lua环境
	static void ReloadLuaWithoutDeleteRoom()
	{
#define _(offset,...) auto f_##offset = (void(__fastcall*)(__VA_ARGS__))((char*)isaac + offset)
		// 输出日志
		inject::LogPrintf(0, "Lua is resetting!\n");
		// 卸载lua环境
		_(0x40AE00, isaac::LuaVM*);
		f_0x40AE00(isaac->luaVM);
		// 加载lua环境
		_(0x3FCB00, isaac::LuaVM*, LPCVOID, bool);
		f_0x3FCB00(isaac->luaVM, NULL, isaac->luaVM->luaDebug);
		// 清除mod列表
		_(0x4702F0, isaac::ModManager&);
		f_0x4702F0(isaac->fileManager->modManager);
		// 创建mod列表
		_(0x470B40, isaac::ModManager&);
		f_0x470B40(isaac->fileManager->modManager);
		// 重新加载着色器
		_(0x46F2B0, isaac::ModManager&);
		f_0x46F2B0(isaac->fileManager->modManager);
		// 重新加载精灵和字体
		_(0x4AF200);
		f_0x4AF200();
		// 重新加载xml
		_(0x46DAE0, isaac::ModManager&);
		f_0x46DAE0(isaac->fileManager->modManager);
#undef _
	}
}
