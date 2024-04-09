#include <render.hpp>
#include <utils.hpp>
#include <imgui/imgui.h>
namespace render_ {
    bool Render() {
        bool openWindow = true;
        ImGui::Begin("##IsaacSocket_Window", &openWindow);
        static HWND hWnd;
        if (!hWnd)
        {
            hWnd = (HWND)ImGui::GetWindowViewport()->PlatformHandle;
            if (hWnd)
            {
                SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            }
        }

        static bool console;
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

        if (ImGui::Button("打开数据目录"))
        {
            ShellExecuteW(nullptr, L"open", utils::GetDataFilePathW(L".").c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        }
        if (ImGui::Button("button2")) {

        }
        if (ImGui::Button("button3")) {

        }

        ImGui::End();
        return !openWindow;
    }
}