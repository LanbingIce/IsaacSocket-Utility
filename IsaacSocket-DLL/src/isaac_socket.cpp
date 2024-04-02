#include "isaac_socket.hpp"
#include "lua.hpp"
#include "state.hpp"
#include "module.hpp"
#include "isaac_image.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "inject.hpp"
#include "reload.hpp"
#include "config.hpp"

#include <imsdk/TIMManager.h>
#include <glad/glad.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM // 解决 GL 函数重定义问题
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_win32.h>

namespace _isaac_socket
{
    static int Connect(lua_State* L) {
        local.connectionState = state::CONNECTED;
        luaL_dostring(L, "IsaacSocket = _ISAAC_SOCKET.IsaacSocket");

        FAST_MOD_CALLBACK_BEGIN(ISMC_POST_OPEN);
        FAST_MOD_CALLBACK_END();
        return 0;
    }

    static int Disconnect(lua_State* L) {
        FAST_MOD_CALLBACK_BEGIN(ISMC_PRE_CLOSE);
        FAST_MOD_CALLBACK_END();
        TIMUninit();
        local.MTRandomLockedValue = 0;
        isaac.game->console.state += isaac.game->console.state < 0 ? 5 : 0;
        isaac.game->pauseMenu.state = std::abs(isaac.game->pauseMenu.state);
        VAR_WRITE(isaac.FrameInterval, 1.0 / 60);
        luaL_dostring(L, "IsaacSocket = nil");
        local.connectionState = state::DISCONNECTED;
        std::lock_guard lock(local.mutex);
        local.pResults.clear();
        return 0;
    }

    static void _InitLua() {
        RegisterModule::InitAllModules();

        lua_getglobal(L, "_ISAAC_SOCKET");

        MODULE_FUNC(Connect);
        MODULE_FUNC(Disconnect);

        std::ostringstream oss;
        oss << "_ISAAC_SOCKET.version="
            << "\"" << global.version << "\""
            << "_ISAAC_SOCKET.tasks={}"
            << "_ISAAC_SOCKET.taskCallbacks={}"
            << "_ISAAC_SOCKET.openCallbacks={}"
            << "_ISAAC_SOCKET.messageCallbacks={}"
            << "_ISAAC_SOCKET.closedCallbacks={}"
            << "_ISAAC_SOCKET.errorCallbacks={}";
        luaL_dostring(L, oss.str().c_str());
    }
}

namespace isaac_socket
{
    bool TryInitLua() {
        bool result = false;
        if (lua_getglobal(L, "_ISAAC_SOCKET") == LUA_TTABLE)
        {
            lua_pushstring(L, "Connect");
            lua_gettable(L, -2);
            if (!lua_iscfunction(L, -1))
            {
                _isaac_socket::_InitLua();
            }
            result = true;
        }
        return result;
    }

    // 进行一次 “日志输出”
    void LogOutput(const char* text, uint32_t type)
    {
        inject::LogPrintf(type % 4, "%s", text);
    }

    // 进行一次 “控制台输出”
    void ConsoleOutput(string text, uint32_t color)
    {
        inject::ConsoleOutput(isaac.game->console, NULL, text, color, 0x96);
    }

    // 进行一次 “执行控制台指令”
    void ExecuteCommand(string commandText)
    {
        inject::ExecuteCommand(isaac.game->console, NULL, commandText, 0, 0);
    }

    // 手动发送一条窗口过程消息
    LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        return inject::WndProc(hWnd, uMsg, wParam, lParam);
    }

    // 重新载入lua环境
    void ReloadLua()
    {
        if (!isaac.mainMenu || local.isRepentogon)
        {
            // 输出日志
            inject::LogPrintf(0, "Lua is resetting!\n");
            // 卸载lua环境
            FUNC(0x40AE00, void, FASTCALL, isaac_image::LuaEngine*);
            f_0x40AE00(isaac.luaEngine);
            // 加载lua环境
            FUNC(0x3FCB00, void, FASTCALL, isaac_image::LuaEngine*, LPCVOID, bool);
            f_0x3FCB00(isaac.luaEngine, NULL, isaac.luaEngine->luaDebug);
            // 清除mod列表
            FUNC(0x4702F0, void, FASTCALL, isaac_image::ModManager&);
            f_0x4702F0(isaac.manager->modManager);
            // 创建mod列表
            FUNC(0x470B40, void, FASTCALL, isaac_image::ModManager&);
            f_0x470B40(isaac.manager->modManager);
            // 重新加载着色器
            FUNC(0x46F2B0, void, FASTCALL, isaac_image::ModManager&);
            f_0x46F2B0(isaac.manager->modManager);
            // 重新加载精灵和字体
            FUNC(0x4AF200, void, FASTCALL);
            f_0x4AF200();
            // 重新加载xml
            FUNC(0x46DAE0, void, FASTCALL, isaac_image::ModManager&);
            f_0x46DAE0(isaac.manager->modManager);
        }
        else
        {
            FUNC(0x473410, void, FASTCALL, isaac_image::ModManager&);
            f_0x473410(isaac.manager->modManager);
        }
    }

    // 设置GLFW的接收字符回调，使得直接设置控制台state的方式打开控制台也可以输入字符
    void SetGLFWCharacter() {
        isaac.window->character = (char*)&isaac + 0x25ECE0;
    }

    void InitByMainThread() {
        gladLoadGL();
        SetGLFWCharacter();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.FontAllowUserScaling = true;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

        string fontFile = config::Get<string>("IsaacSocket.FontFile");

        auto ifs = std::ifstream(fontFile);

        if (ifs)
        {
            float fontSize = config::Get<float>("IsaacSocket.FontSize");
            if (fontSize < 8 || fontSize > 64)
            {
                fontSize = 32;
                config::Set("IsaacSocket.FontSize", fontSize);
            }
            io.Fonts->AddFontFromFileTTF(fontFile.c_str(), fontSize, nullptr, io.Fonts->GetGlyphRangesChineseFull());
        }

        string path = utils::GetDataFilePath("VonwaonBitmap-16px.ttf");
        io.Fonts->AddFontFromFileTTF(path.c_str(), 32.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
        io.Fonts->AddFontFromFileTTF(path.c_str(), 16.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());

        static const string iniFileName = utils::GetDataFilePath("imgui.ini");
        static const string logFileName = utils::GetDataFilePath("imgui_log.txt");

        io.IniFilename = iniFileName.c_str();
        io.LogFilename = logFileName.c_str();

        switch (config::Get<int>("IsaacSocket.StyleColors"))
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

    void AllocConsole() {
        ::AllocConsole();
        SetForegroundWindow(local.hWnd);
        cw("已启用系统控制台！");
        cw("如需关闭此窗口，请先禁用系统控制台！否则游戏也会退出");
    }

    void FreeConsole() {
        cw("已禁用系统控制台，请手动关闭此窗口");
        ::FreeConsole();
    }

    // 全屏/取消全屏
    void FullScreen(bool fullScreen) {
        FUNC(0x4810E0, void, __stdcall, bool);
        f_0x4810E0(fullScreen);
    }

    // 音乐音量
    void MusicVolume(float musicVolume) {
        FUNC(0x481080, void, __stdcall, float);
        f_0x481080(musicVolume);
    }

    // 垂直同步
    void VSync(bool vSync) {
        FUNC(0x481280, void, __stdcall, bool);
        f_0x481280(vSync);
    }
}
