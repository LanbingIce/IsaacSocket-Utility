#pragma once

#include "pch.h"
#include "state.hpp"
#include "utils.hpp"
#include "function.hpp"
#include "modules/_isaac_socket.hpp"
#include "config.hpp"

#include <imgui/imgui.h>

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define CHECK_INIT()if (!local.initialized)return 0
#define CHECK_STATE()if (global->connectionState != state::CONNECTED)return 0
namespace callback {

	// SwapBuffers之前，只要游戏进程存在就一直触发，返回1则取消此次交换
	static int PreSwapBuffers(HDC hdc)
	{
		switch (global->connectionState) {
		case state::CONNECTING:
			if (!local.initialized)
			{
				local.hWnd = WindowFromDC(hdc);
				function::IsaacSocketFirstTimeInit();
				local.initialized = true;
			}
			_isaac_socket::Init();
			global->connectionState = state::CONNECTED;
			break;
		case state::CONNECTED:
			function::IsaacSocketUpdate();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			bool font16 = local.isaac->screenPointScale == 1.0f;
			if (font16)
			{
				ImGui::PushFont(local.font16);
			}

#define MENU_BEGIN(name)if (ImGui::BeginMenu(#name)){
#define MENU_END()ImGui::EndMenu();}
#define MENU_ITEM(name,selected,e)if (ImGui::MenuItem(#name, nullptr, selected)){e;}

			if ((local.isaac->game->pauseMenu.state || local.menuBarDisplayMode == state::ALWAYS || local.menuBarDisplayMode == state::TAB_HOLD && GetAsyncKeyState(VK_TAB) & 0x8000) && ImGui::BeginMainMenuBar())
			{
				MENU_BEGIN(IsaacSockets管理);
				MENU_ITEM(打开控制台, local.allocConsole, local.allocConsole = !local.allocConsole; if (local.allocConsole)function::AllocConsole(); else function::FreeConsole(););
				MENU_END();
				MENU_BEGIN(界面设置);
				MENU_BEGIN(主菜单条显示方式);
				MENU_ITEM(默认, local.menuBarDisplayMode == state::NEVER, local.menuBarDisplayMode = state::NEVER; config::SetInt({ "IsaacSocket", "MenuBar" }, 0));
				MENU_ITEM(按下Tab键时, local.menuBarDisplayMode == state::TAB_HOLD, local.menuBarDisplayMode = state::TAB_HOLD; config::SetInt({ "IsaacSocket","MenuBar" }, 1));
				MENU_ITEM(总是显示, local.menuBarDisplayMode == state::ALWAYS, local.menuBarDisplayMode = state::ALWAYS; config::SetInt({ "IsaacSocket", "MenuBar" }, 2));
				MENU_END();
				MENU_BEGIN(皮肤);
				MENU_ITEM(默认, local.styleColor == state::CLASSIC, local.styleColor = state::CLASSIC; ImGui::StyleColorsClassic(); config::SetInt({ "IsaacSocket", "StyleColors" }, 0));
				MENU_ITEM(浅色, local.styleColor == state::LIGHT, local.styleColor = state::LIGHT; ImGui::StyleColorsLight(); config::SetInt({ "IsaacSocket", "StyleColors" }, 1));
				MENU_ITEM(深色, local.styleColor == state::DARK, local.styleColor = state::DARK; ImGui::StyleColorsDark(); config::SetInt({ "IsaacSocket","StyleColors" }, 2));
				MENU_END();
				MENU_END();

				FAST_MOD_CALLBACK_BEGIN(ISMC_IMGUI_MAIN_MENU_BAR_RENDER);
				FAST_MOD_CALLBACK_END();
				ImGui::EndMainMenuBar();
			}

#undef MENU_BEGIN
#undef MENU_END
#undef MENU_ITEM

			FAST_MOD_CALLBACK_BEGIN(ISMC_IMGUI_RENDER);
			FAST_MOD_CALLBACK_END();

			if (font16)
			{
				ImGui::PopFont();
			}

			ImGui::Render();

			// Draw the overlay
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			MOD_CALLBACK_BEGIN(ISMC_PRE_SWAP_BUFFERS);
			MOD_CALLBACK_CALL();
			MOD_CALLBACK_END();
			break;
		}
		CHECK_INIT();
		FAST_MOD_CALLBACK_BEGIN(_ISAAC_SOCKET_UPDATE);
		FAST_MOD_CALLBACK_END();
		return 0;
	}

	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置，返回1则取消此次指令
	static int OnExecuteCommand(string& text, int unknow, LPCVOID unknow_point_guess)
	{
		CHECK_STATE();

		MOD_CALLBACK_BEGIN(ISMC_PRE_EXECUTE_CMD);
		MOD_CALLBACK_ARG(lstring, text.c_str(), text.size());
		MOD_CALLBACK_CALL();
		if (local.lua.lua_isstring(L, -1))
		{
			text = local.lua.lua_tolstring(L, -1, nullptr);
		}
		else MOD_CALLBACK_END();
		if (text.size() == 0)
		{
			return 1;
		}
		if (text == "test")
		{
		cw(	config::GetInt({"IsaacSocket","MenuBar"}));
			//function::ExecuteCommand("g k1");
			//function::ConsoleOutput("test");
		}

		if (text == "lualua")
		{
			local.needReload = true;
		}

		if (text == "luadll")
		{
			//local.needReloadDll = true;
		}

		return 0;
	}

	// 控制台输出回调，时机在控制台输出函数的起始位置，返回1则取消此次输出
	static int OnConsoleOutput(string& text, uint32_t color, int32_t type)
	{
		CHECK_STATE();

		MOD_CALLBACK_BEGIN(ISMC_PRE_CONSOLE_OUTPUT);
		MOD_CALLBACK_ARG(lstring, text.c_str(), text.size());
		MOD_CALLBACK_ARG(integer, color);
		MOD_CALLBACK_CALL();

		if (local.lua.lua_isstring(L, -1))
		{
			text = local.lua.lua_tolstring(L, -1, nullptr);
		}
		else MOD_CALLBACK_END();

		return 0;
	}

	// 窗口消息回调，返回1则拦截此次消息
	static int PreWndProc(LPCVOID _, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
#define _(name,paramType,...)MOD_CALLBACK_BEGIN(name);MOD_CALLBACK_ARG(paramType,__VA_ARGS__);MOD_CALLBACK_CALL();MOD_CALLBACK_END();
		CHECK_INIT();

		char buffer[4]{};
		char* u8 = buffer;

		if (uMsg == WM_CHAR)
		{
			if (local.charsInputBuffer[0] < 0)
			{
				local.charsInputBuffer[1] = wParam;
				wchar_t* u16 = (wchar_t*)&wParam;
				utils::AnsiToU16(local.charsInputBuffer, u16, 2);
				local.charsInputBuffer[0] = 0;
				local.charsInputBuffer[1] = 0;
				utils::U16ToU8(u16, u8, 4);
			}
			else
			{
				local.charsInputBuffer[0] = wParam;
				if (local.charsInputBuffer[0] < 0)
				{
					return 1;
				}
				u8 = local.charsInputBuffer;
			}
		}

		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		{
			return 1;
		}

		CHECK_STATE();

		const ImGuiIO& io = ImGui::GetIO();

		if (io.WantCaptureMouse && (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP || uMsg == WM_MOUSEWHEEL || uMsg == WM_MOUSEMOVE)) {
			return 1;
		}

		if (io.WantCaptureKeyboard && (uMsg == WM_KEYDOWN || uMsg == WM_CHAR))
		{
			return 1;
		}

		switch (uMsg)
		{
		case WM_CHAR:
			if (!std::iscntrl(wParam))
			{
				_(ISMC_PRE_CHAR_INPUT, string, u8);
			}
			break;
		case WM_KEYDOWN:
			_(ISMC_PRE_KEY_DOWN, integer, wParam);
			break;
		}
		return 0;
#undef _
	}
}
#undef CHECK_STATE
#undef CHECK_INIT