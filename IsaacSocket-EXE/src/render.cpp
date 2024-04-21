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