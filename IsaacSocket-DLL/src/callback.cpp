#include "callback.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "isaac_socket.hpp"
#include "config.hpp"
#include "module.hpp"
#include "isaac_socket.hpp"
#include "udata.hpp"
#include "result.hpp"

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui.h>
#include <ImGuiFileDialog/ImGuiFileDialog.h>

namespace callback {

    // 小彭老师专用代码开始
#ifndef __MINGW32__
#define CHECK_RELOAD() // 不影响msvc
#else
#define CHECK_RELOAD() \
    static int reloadCounter = 0; \
    ++reloadCounter; \
    if (reloadCounter>30&&getenv("IsaacSocketFromClient")&&LuaReady()) { \
        if (local.connectionState == state::DISCONNECTED) { \
            cw("auto ready"); \
            local.connectionState=state::CONNECTING; \
        } \
        if (reloadCounter % 30 == 0) { \
            if (reloadLibraryMain("IsaacSocket.dll", true)) { \
                cw("auto reloaded dll"); \
                return 0; \
            } \
        } \
    }
    static bool LuaReady() {
        isaac_image::LuaEngine* luaEngine = isaac.luaEngine;
        if (!luaEngine) {
            return false;
        }
        lua_State* L = luaEngine->L;
        if (!L) {
            return false;
        }
        LuaGuard luaGuard;
        lua_getglobal(L, "_ISAAC_SOCKET");
        bool ok = !lua_isnoneornil(L, -1);
        if (ok) {
            lua_pushstring(L, "IsaacSocket");
            lua_gettable(L, -2);
            ok = !lua_isnoneornil(L, -1);
            if (ok) {
                lua_setglobal(L, "IsaacSocket");
            }
        }
        return ok;
    }
#endif
    // 小彭老师专用代码结束
    static string currentPath = "C:\\Windows\\Fonts";

    static bool showDemoWindow = false;
    static bool showAboutWindow = false;
    static bool showDebugLogWindow = false;
    static bool showUserGuide = false;
    static bool showISAbout = false;

    static double lastMoveTime;

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

    static void ShowSelectFont() {
        IGFD::FileDialogConfig config;
        config.path = currentPath;
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "选择字体文件", "字体文件 (*.ttf *.otf){.ttf,.otf,.TTF,.OTF}", config);
    }

#define MENU_BEGIN(name)if (ImGui::BeginMenu(name)){
#define MENU_END()ImGui::EndMenu();}
#define MENU_ITEM(name,selected,e)if (ImGui::MenuItem(name, nullptr, selected)){e;}

    static int ImGuiMainMenuBarRender() {

        MENU_BEGIN("IsaacSocket");
        MENU_ITEM("启用系统控制台", local.allocConsole, local.allocConsole = !local.allocConsole; if (local.allocConsole)isaac_socket::AllocConsole(); else isaac_socket::FreeConsole(););
        MENU_ITEM("小退并重载Lua环境", false, local.connectionState = state::RELOAD_LUA; local.reloadLuaState = state::EXIT);
        MENU_BEGIN("实验性功能");
        MENU_ITEM("重载Lua环境", false, local.connectionState = state::RELOAD_LUA; local.reloadLuaState = state::RELOAD);
        MENU_END();
        MENU_ITEM("打开数据目录", false, ShellExecuteW(nullptr, L"open", utils::GetDataFilePathW(L".").c_str(), nullptr, nullptr, SW_SHOWNORMAL));
        ImGui::Separator();
        MENU_ITEM("关于 IsaacSocket", false, showISAbout = true);
        MENU_END();
        MENU_BEGIN("ImGui");
        MENU_BEGIN("配色");
        int styleColors = config::Get<int>("IsaacSocket.StyleColors");
        MENU_ITEM("默认", styleColors == state::CLASSIC, ImGui::StyleColorsClassic(); config::Set("IsaacSocket.StyleColors", 0));
        MENU_ITEM("浅色", styleColors == state::LIGHT, ImGui::StyleColorsLight(); config::Set("IsaacSocket.StyleColors", 1));
        MENU_ITEM("深色", styleColors == state::DARK, ImGui::StyleColorsDark(); config::Set("IsaacSocket.StyleColors", 2));
        MENU_END();
        MENU_BEGIN("选择字体");
        ImGuiIO& io = ImGui::GetIO();
        for (ImFont* font : io.Fonts->Fonts)
        {
            ImGui::PushID(font);
            MENU_ITEM(font->GetDebugName(), font == ImGui::GetFont(), io.FontDefault = font);
            ImGui::PopID();
        }
        MENU_ITEM("设置自定义字体", false, ShowSelectFont());
        ImGui::SetItemTooltip("设置之后需要重启游戏才能生效，请务必记得设置字体大小");
        MENU_BEGIN("设置自定义字体尺寸");
        float fontSize = config::Get<float>("IsaacSocket.FontSize");
        for (size_t i = 8; i <= 64; i++)
        {
            MENU_ITEM((std::to_string(i) + "##字体尺寸").c_str(), fontSize == i, config::Set("IsaacSocket.FontSize", (float)i));
        }
        MENU_END();
        MENU_ITEM("清除自定义字体", false, config::Set("IsaacSocket.FontFile", ""));
        MENU_END();
        ImGui::Separator();
        MENU_BEGIN("调试工具");
        MENU_ITEM("示例窗口", false, showDemoWindow = true);
        MENU_ITEM("调试日志", false, showDebugLogWindow = true);
        MENU_END();
        ImGui::Separator();
        MENU_ITEM("操作说明", false, showUserGuide = true);
        MENU_ITEM("关于ImGui", false, showAboutWindow = true);
        MENU_END();
        return 0;
    }

#undef MENU_BEGIN
#undef MENU_END
#undef MENU_ITEM

    static int ImGuiWindowRender() {
        if (showDemoWindow)
        {
            ImGui::ShowDemoWindow(&showDemoWindow);
        }
        if (showAboutWindow)
        {
            ImGui::ShowAboutWindow(&showAboutWindow);
        }
        if (showDebugLogWindow)
        {
            ImGui::ShowDebugLogWindow(&showDebugLogWindow);
        }
        if (showUserGuide)
        {
            ShowUserGuide(&showUserGuide);
        }
        if (showISAbout)
        {
            ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
            if (ImGui::Begin("关于 IsaacSocket", &showISAbout, flags))
            {
                lua_getglobal(L, "_ISAAC_SOCKET");
                lua_pushstring(L, "modVersion");
                lua_gettable(L, -2);
                ARG_DEF(-1, string, const char*, ver, "1.0");
                ImGui::Text("IsaacSocket");
                ImGui::Text("版本号：%s-%s", global.version, ver);
                ImGui::End();
            }
        }

        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
            if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
                string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                currentPath = ImGuiFileDialog::Instance()->GetCurrentPath();
                config::Set("IsaacSocket.FontFile", filePathName);
                // action
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }

        return 0;
    }

    static bool IsMouseMove() {
        ImGuiIO& io = ImGui::GetIO();
        if (io.MousePos.x >= 0 && io.MousePos.y >= 0 && io.MousePos.x < io.DisplaySize.x && io.MousePos.y < io.DisplaySize.y && (io.MouseDelta.x != 0 || io.MouseDelta.y != 0))
        {
            lastMoveTime = ImGui::GetTime();
        }
        return ImGui::GetTime() - lastMoveTime <= 1;
    }

    static int ImGuiRender(bool render) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (render)
        {
            if (IsMouseMove())
            {
                static bool show = true;

                ImGui::Begin("##IsaacSocket悬浮窗", &show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
                ImGui::Text("IsaacSocket");
                ImGui::SetWindowFontScale(1.0f);

                if (ImGui::IsWindowHovered())
                {
                    lastMoveTime = ImGui::GetTime();
                }
                if (ImGui::BeginPopupContextWindow())
                {
                    lastMoveTime = ImGui::GetTime();
                    ImGuiMainMenuBarRender();
                    FAST_MOD_CALLBACK_BEGIN(ISMC_IMGUI_MAIN_MENU_BAR_RENDER);
                    FAST_MOD_CALLBACK_END();
                    ImGui::EndPopup();
                }
                ImGui::End();
            }

            ImGuiWindowRender();

            FAST_MOD_CALLBACK_BEGIN(ISMC_IMGUI_RENDER);
            FAST_MOD_CALLBACK_END();

            ImGui::Render();

            // Draw the overlay
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        else
        {
            ImGui::EndFrame();
        }

        return 0;
    }

    static void RunTaskCallbacks(lua_State* L = ::L) {
        LuaGuard luaGuard;

        lua_getglobal(L, "_ISAAC_SOCKET");
        lua_pushstring(L, "tasks");
        lua_gettable(L, -2);
        lua_pushstring(L, "taskCallbacks");
        lua_gettable(L, -3);

        while (true) {
            const auto& _result = result::Pop();
            if (!_result.has_value())
            {
                break;
            }
            for (auto& f : result::RegisterResultType::resultCallbacks)
            {
                if (f(_result, L))
                {
                    break;
                }
            }
        }
    }

#define CHECK_INIT()if (local.connectionState == state::INIT)return 0
#define CHECK_STATE()if (local.connectionState != state::CONNECTED)return 0

    // SwapBuffers之前，只要游戏进程存在就一直触发，返回1则取消此次交换
    int PreSwapBuffers(const HDC hdc)
    {
        CHECK_RELOAD();
        if (local.connectionState == state::INIT)
        {
            local.hWnd = WindowFromDC(hdc);
            isaac_socket::InitByMainThread();
            local.connectionState = state::DISCONNECTED;
        }
        LuaGuard luaGuard;
        if (!isaac_socket::TryInitLua())
        {
            return 0;
        }
        FAST_MOD_CALLBACK_BEGIN(_ISAAC_SOCKET_UPDATE);
        if (luaL_len(L, -5) != 1)
        {
            return 0;
        }
        FAST_MOD_CALLBACK_END();

        ImGuiRender(local.connectionState == state::CONNECTED);

        switch (local.connectionState)
        {
        case state::RELOAD_LUA:
            switch (local.reloadLuaState)
            {
            case state::EXIT:
                isaac.manager->needExit = true;
                local.reloadLuaState = state::SWITCH_PAGE;
                break;
            case state::SWITCH_PAGE:
                isaac.mainMenu->page = 3;
                [[fallthrough]];
            case state::RELOAD:
                isaac_socket::ReloadLua();
                break;
            }
            break;
        case state::CONNECTED:
            RunTaskCallbacks();
            MOD_CALLBACK_BEGIN(ISMC_PRE_SWAP_BUFFERS);
            MOD_CALLBACK_CALL();
            MOD_CALLBACK_END();
            break;
        }
        return 0;
    }

    // 执行控制台指令回调，时机在执行控制台指令函数的起始位置，返回1则取消此次指令
    int OnExecuteCommand(const isaac_image::Console& console, string& text, const int unknow, const LPCVOID unknow_point_guess)
    {
        CHECK_STATE();
        LuaGuard luaGuard;
        MOD_CALLBACK_BEGIN(ISMC_PRE_EXECUTE_CMD);
        MOD_CALLBACK_ARG(lstring, text.c_str(), text.size());
        MOD_CALLBACK_CALL();
        if (lua_isstring(L, -1))
        {
            text = lua_tolstring(L, -1, nullptr);
        }
        else MOD_CALLBACK_END();
        if (text.size() == 0)
        {
            return 1;
        }
        if (text == "test")
        {

        }
        return 0;
    }

    // 控制台输出回调，时机在控制台输出函数的起始位置，返回1则取消此次输出
    int OnConsoleOutput(const isaac_image::Console& console, string& text, const uint32_t color, const int type_guess)
    {
        CHECK_STATE();
        LuaGuard luaGuard;
        MOD_CALLBACK_BEGIN(ISMC_PRE_CONSOLE_OUTPUT);
        MOD_CALLBACK_ARG(lstring, text.c_str(), text.size());
        MOD_CALLBACK_ARG(integer, color);
        MOD_CALLBACK_CALL();

        if (lua_isstring(L, -1))
        {
            text = lua_tolstring(L, -1, nullptr);
        }
        else MOD_CALLBACK_END();

        return 0;
    }

    // 窗口消息回调，返回1则拦截此次消息
    int PreWndProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
    {
#define _(name,paramType,...)MOD_CALLBACK_BEGIN(name);MOD_CALLBACK_ARG(paramType,__VA_ARGS__);MOD_CALLBACK_CALL();MOD_CALLBACK_END();
        CHECK_INIT();

        if (uMsg != WM_CHAR && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        {
            return 1;
        }

        CHECK_STATE();

        ImGuiIO& io = ImGui::GetIO();
        wchar_t wChar = wParam;

        if (uMsg == WM_CHAR)
        {
            static char buffer[2];
            if (buffer[0])
            {
                buffer[1] = wParam;
                MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buffer, 2, &wChar, 1);
                buffer[0] = 0;
            }
            else if (IsDBCSLeadByte(wParam))
            {
                buffer[0] = wParam;
                return 0;
            }

            io.AddInputCharacter(wChar);
        }

        if (io.WantCaptureMouse && (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP || uMsg == WM_MOUSEWHEEL || uMsg == WM_MOUSEMOVE)) {
            return 1;
        }

        if (io.WantCaptureKeyboard && (uMsg == WM_KEYDOWN || uMsg == WM_CHAR))
        {
            return 1;
        }

        LuaGuard luaGuard;
        switch (uMsg)
        {
        case WM_CHAR:
            if (!std::iswcntrl(wChar))
            {
                char u8[4]{};
                WideCharToMultiByte(CP_UTF8, 0, &wChar, 1, u8, 3, nullptr, nullptr);
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
#undef CHECK_RELOAD