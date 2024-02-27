#pragma once

#include "pch.h"
#include "async.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "function.hpp"
#include "config.hpp"
#include "isaac_socket.hpp"
#include <imgui/imgui.h>

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define CHECK_INIT()if (!local.initialized)return 0
#define CHECK_STATE()if (global->connectionState != state::CONNECTED)return 0
namespace callback {

	// 小彭老师专用代码开始
#ifndef __MINGW32__
#define CHECK_RELOAD() // 不影响msvc
#else
#define CHECK_RELOAD() \
    static int reloadCounter = 0; \
    ++reloadCounter; \
    if (reloadCounter>30&&getenv("IsaacSocketFromClient")&&LuaReady()) { \
        if (global->connectionState == state::DISCONNECTED) { \
            cw("auto ready"); \
            global->connectionState=state::CONNECTING; \
        } \
        if (reloadCounter % 30 == 0) { \
            if (reloadLibraryMain("IsaacSocket.dll", true)) { \
                cw("auto reloaded dll"); \
                return 0; \
            } \
        } \
    }
	static bool LuaReady() {
		isaac::LuaEngine* luaEngine = local.isaac->luaEngine;
		if (!luaEngine) {
			return false;
		}
		lua_State* L = luaEngine->L;
		if (!L) {
			return false;
		}
		int top = local.lua.lua_gettop(L);
		local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
		bool ok = !local.lua.lua_isnoneornil(L, -1);
		if (ok) {
			local.lua.lua_pushstring(L, "IsaacSocket");
			local.lua.lua_gettable(L, -2);
			ok = !local.lua.lua_isnoneornil(L, -1);
			if (ok) {
				local.lua.lua_setglobal(L, "IsaacSocket");
			}
		}
		local.lua.lua_settop(L, top);
		return ok;
	}
#endif
	// 小彭老师专用代码结束

#define CHECK_INIT()if (!local.initialized)return 0
#define CHECK_STATE()if (global->connectionState != state::CONNECTED)return 0

	static void ShowUserGuide(bool* p_open)
	{
		if (p_open)
		{
			ImGui::Begin("操作说明", p_open);
			ImGuiIO& io = ImGui::GetIO();
			ImGui::BulletText("双击标题栏可以折叠窗口。");
			ImGui::BulletText(
				"鼠标左键拖动窗口右下角可以改变尺寸\n"
				"（双击右下角可以自动调节尺寸）。");
			ImGui::BulletText("CTRL+单击鼠标左键 可以在滑动或拖动控件中直接输入值。");
			ImGui::BulletText("使用 TAB / SHIFT+TAB 键在可键盘编辑的字段之间循环切换。");
			if (io.FontAllowUserScaling)
				ImGui::BulletText("CTRL+鼠标滚轮可以缩放窗口内容。");
			ImGui::BulletText("当你输入文本时：\n");
			ImGui::Indent();
			ImGui::BulletText("CTRL+左/右方向键可以进行单词跳转。");
			ImGui::BulletText("CTRL+A 或者 双击鼠标左键可以全选。");
			ImGui::BulletText("CTRL+X/C/V 可以进行剪切/复制/粘贴。");
			ImGui::BulletText("CTRL+Z,CTRL+Y 可以进行 撤销/重做。");
			ImGui::BulletText("ESC键：完全撤销本次编辑。");
			ImGui::Unindent();
			ImGui::End();
		}
	}

#define MENU_BEGIN(name)if (ImGui::BeginMenu(#name)){
#define MENU_END()ImGui::EndMenu();}
#define MENU_ITEM(name,selected,e)if (ImGui::MenuItem(#name, nullptr, selected)){e;}

	static int ImGuiMainMenuBarRender() {

		MENU_BEGIN(IsaacSocket);
		MENU_ITEM(启用系统控制台, local.allocConsole, local.allocConsole = !local.allocConsole; if (local.allocConsole)function::AllocConsole(); else function::FreeConsole(););
		MENU_BEGIN(实验性功能);
		MENU_ITEM(重载lua, false, local.needReload = true);
		MENU_END();
		ImGui::Separator();
		MENU_ITEM(关于 IsaacSocket, false, local.imgui.ShowISAbout = true);
		MENU_END();
		MENU_BEGIN(ImGui);
		MENU_BEGIN(显示主菜单条);
		MENU_ITEM(默认, local.menuBarDisplayMode == state::NEVER, local.menuBarDisplayMode = state::NEVER; config::SetInt({ "IsaacSocket", "MenuBar" }, 0));
		MENU_ITEM(按下Tab键时, local.menuBarDisplayMode == state::TAB_HOLD, local.menuBarDisplayMode = state::TAB_HOLD; config::SetInt({ "IsaacSocket","MenuBar" }, 1));
		MENU_ITEM(总是显示, local.menuBarDisplayMode == state::ALWAYS, local.menuBarDisplayMode = state::ALWAYS; config::SetInt({ "IsaacSocket", "MenuBar" }, 2));
		MENU_END();
		MENU_BEGIN(配色);
		MENU_ITEM(默认, local.styleColor == state::CLASSIC, local.styleColor = state::CLASSIC; ImGui::StyleColorsClassic(); config::SetInt({ "IsaacSocket", "StyleColors" }, 0));
		MENU_ITEM(浅色, local.styleColor == state::LIGHT, local.styleColor = state::LIGHT; ImGui::StyleColorsLight(); config::SetInt({ "IsaacSocket", "StyleColors" }, 1));
		MENU_ITEM(深色, local.styleColor == state::DARK, local.styleColor = state::DARK; ImGui::StyleColorsDark(); config::SetInt({ "IsaacSocket","StyleColors" }, 2));
		MENU_END();
		ImGui::Separator();
		MENU_BEGIN(调试工具);
		MENU_ITEM(示例窗口, local.imgui.ShowDemoWindow, local.imgui.ShowDemoWindow = !local.imgui.ShowDemoWindow);
		MENU_ITEM(调试日志, local.imgui.ShowDebugLogWindow, local.imgui.ShowDebugLogWindow = !local.imgui.ShowDebugLogWindow);
		MENU_END();
		ImGui::Separator();
		MENU_ITEM(操作说明, local.imgui.ShowUserGuide, local.imgui.ShowUserGuide = !local.imgui.ShowUserGuide);
		MENU_ITEM(关于ImGui, local.imgui.ShowAboutWindow, local.imgui.ShowAboutWindow = !local.imgui.ShowAboutWindow);
		MENU_END();
		return 0;
	}

#undef MENU_BEGIN
#undef MENU_END
#undef MENU_ITEM

	static int ImGuiWindowRender() {
		if (local.imgui.ShowDemoWindow)
		{
			ImGui::ShowDemoWindow(&local.imgui.ShowDemoWindow);
		}
		if (local.imgui.ShowAboutWindow)
		{
			ImGui::ShowAboutWindow(&local.imgui.ShowAboutWindow);
		}
		if (local.imgui.ShowDebugLogWindow)
		{
			ImGui::ShowDebugLogWindow(&local.imgui.ShowDebugLogWindow);
		}
		if (local.imgui.ShowUserGuide)
		{
			ShowUserGuide(&local.imgui.ShowUserGuide);
		}
		if (local.imgui.ShowISAbout)
		{
			ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
			if (ImGui::Begin("关于 IsaacSocket", &local.imgui.ShowISAbout, flags))
			{
				lua_State* L = local.isaac->luaEngine->L;
				size_t top = local.lua.lua_gettop(L);
				local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
				local.lua.lua_pushstring(L, "modVersion");
				local.lua.lua_gettable(L, -2);
				ARG_DEF(-1, string, const char*, ver, "1.0");
				local.lua.lua_settop(L, top);
				ImGui::Text("IsaacSocket");
				ImGui::Text("版本号：%s-%s", global->version, ver);
				ImGui::End();
			}
		}
		return 0;
	}

	static int ImGuiRender() {

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		bool font16 = local.isaac->screenPointScale == 1.0f;
		if (font16)
		{
			ImGui::PushFont(local.font16);
		}

		if ((local.isaac->game->pauseMenu.state || local.menuBarDisplayMode == state::ALWAYS || local.menuBarDisplayMode == state::TAB_HOLD && ImGui::IsKeyDown(ImGuiKey_Tab)) && ImGui::BeginMainMenuBar())
		{
			ImGuiMainMenuBarRender();
			FAST_MOD_CALLBACK_BEGIN(ISMC_IMGUI_MAIN_MENU_BAR_RENDER);
			FAST_MOD_CALLBACK_END();
			ImGui::EndMainMenuBar();
		}

		ImGuiWindowRender();

		FAST_MOD_CALLBACK_BEGIN(ISMC_IMGUI_RENDER);
		FAST_MOD_CALLBACK_END();

		if (font16)
		{
			ImGui::PopFont();
		}

		ImGui::Render();

		// Draw the overlay
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		return 0;
	}

	// SwapBuffers之前，只要游戏进程存在就一直触发，返回1则取消此次交换
	static int PreSwapBuffers(HDC hdc)
	{
		CHECK_RELOAD();
		if (local.initialized)
		{
			FAST_MOD_CALLBACK_BEGIN(_ISAAC_SOCKET_UPDATE);
			FAST_MOD_CALLBACK_END();
		}
		switch (global->connectionState) {
		case state::DISCONNECTED:
			break;
		case state::CONNECTING:
			if (!local.initialized)
			{
				local.hWnd = WindowFromDC(hdc);
				function::IsaacSocketFirstTimeInit();
				local.initialized = true;
			}
			isaac_socket::Init();
			global->connectionState = state::CONNECTED;
			break;
		case state::CONNECTED:
			if (function::IsaacSocketUpdate())
			{
				break;
			}
			async::luaPollPromises(local.isaac->luaEngine->L);
			ImGuiRender();
			MOD_CALLBACK_BEGIN(ISMC_PRE_SWAP_BUFFERS);
			MOD_CALLBACK_CALL();
			MOD_CALLBACK_END();
			break;
		}
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

	static int TIMRecvNewMsgCallback(const char* json_msg_array, const void* user_data)
	{
		FAST_MOD_CALLBACK_BEGIN(ISMC_TIM_NEW_MSG);
		MOD_CALLBACK_ARG(string, json_msg_array);
		FAST_MOD_CALLBACK_END();
		return 0;
	}
	static int TIMCommCallback(int32_t code, const char* desc, const char* json_params, const void* user_data)
	{
		FAST_MOD_CALLBACK_BEGIN(ISMC_TIM_COMM);
		MOD_CALLBACK_ARG(integer, code);
		MOD_CALLBACK_ARG(string, desc);
		MOD_CALLBACK_ARG(string, json_params);
		FAST_MOD_CALLBACK_END();
		return 0;
	}
}
#undef CHECK_STATE
#undef CHECK_INIT
#undef CHECK_RELOAD
