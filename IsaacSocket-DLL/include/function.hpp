#pragma once

#include "pch.h"
#include "isaac.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "inject.hpp"
#include "reload.hpp"

#include <glad/glad.h>

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_win32.h>

namespace function {

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

	// 手动发送一条窗口过程消息
	LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return inject::WndProc(hWnd, uMsg, wParam, lParam);
	}

	// 重新载入lua环境
	static void ReloadLuaWithoutDeleteRoom()
	{
		isaac::IsaacImage* isaac = local.isaac;
		// 输出日志
		inject::LogPrintf(0, "Lua is resetting!\n");
		// 卸载lua环境
		FUNC(0x40AE00, void, FASTCALL, isaac::LuaEngine*);
		f_0x40AE00(isaac->luaEngine);
		// 加载lua环境
		FUNC(0x3FCB00, void, FASTCALL, isaac::LuaEngine*, LPCVOID, bool);
		f_0x3FCB00(isaac->luaEngine, NULL, isaac->luaEngine->luaDebug);
		// 清除mod列表
		FUNC(0x4702F0, void, FASTCALL, isaac::ModManager&);
		f_0x4702F0(isaac->manager->modManager);
		// 创建mod列表
		FUNC(0x470B40, void, FASTCALL, isaac::ModManager&);
		f_0x470B40(isaac->manager->modManager);
		// 重新加载着色器
		FUNC(0x46F2B0, void, FASTCALL, isaac::ModManager&);
		f_0x46F2B0(isaac->manager->modManager);
		// 重新加载精灵和字体
		FUNC(0x4AF200, void, FASTCALL);
		f_0x4AF200();
		// 重新加载xml
		FUNC(0x46DAE0, void, FASTCALL, isaac::ModManager&);
		f_0x46DAE0(isaac->manager->modManager);
	}

	// 设置GLFW的接收字符回调，使得直接设置控制台state的方式打开控制台也可以输入字符
	static void SetGLFWCharacter() {
		local.isaac->window->character = (char*)local.isaac + 0x25ECE0;
	}

	static void IsaacSocketFirstTimeInit() {
		gladLoadGL();
		function::SetGLFWCharacter();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.FontAllowUserScaling = true;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

		std::filesystem::path fontPath = utils::GetDataFilePath("VonwaonBitmap-16px.ttf");
		io.Fonts->AddFontFromFileTTF((const char*)fontPath.u8string().c_str(), 32.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
		local.font16 = io.Fonts->AddFontFromFileTTF((const char*)fontPath.u8string().c_str(), 16.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());

		io.IniFilename = (const char*)local.iniFileName.c_str();
		io.LogFilename = (const char*)local.logFileName.c_str();

		switch (local.styleColor)
		{
		case state::LIGHT:
			ImGui::StyleColorsLight();
			break;
		case state::DARK:
			ImGui::StyleColorsDark();
			break;
		default:
			ImGui::StyleColorsClassic();
			break;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_InitForOpenGL(local.hWnd);
		ImGui_ImplOpenGL3_Init();
	}

	static void IsaacSocketUpdate() {
		if (local.needReloadDll)
		{
			reloadLibraryMain("IsaacSocket.dll");
			local.needReloadDll = false;
			return;
		}

		if (local.needReload)
		{
			local.needReload = false;
			function::ReloadLuaWithoutDeleteRoom();
			return;
		}

		if (local.hConsole)
		{
			PostMessageA(local.hConsole, WM_CLOSE, 0, 0);
			local.hConsole = 0;
		}
	}

	static void AllocConsole() {
		::AllocConsole();
		SetForegroundWindow(local.hWnd);
	}

	static void FreeConsole() {
		local.hConsole = GetConsoleWindow();
		::FreeConsole();
	}
}