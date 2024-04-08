#include <render.hpp>
#include <utils.hpp>
#include <imgui/imgui.h>
namespace render_ {
    bool show_demo_window = true;
    bool show_another_window = false;
    bool Render() {
        bool open = true;
        static bool console;

        ImGui::Begin("##IsaacSocket_Window", &open);
        static HWND hWnd;
        if (!hWnd)
        {
            hWnd = (HWND)ImGui::GetWindowViewport()->PlatformHandle;
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            SetActiveWindow(hWnd);
        }
        if (ImGui::Checkbox("Console", &console))
        {
            if (console)
            {
                AllocConsole();
                SetConsoleOutputCP(CP_UTF8);
                FILE* stream;
                freopen_s(&stream, "CONOUT$", "w", stdout);
            }
            else
            {
                ShowWindow(GetConsoleWindow(), SW_HIDE);
                FreeConsole();
            }
        }

        if (ImGui::Button("button"))
        {
            cout << "测试";
        }

        ImGui::End();
        return !open;
    }
}