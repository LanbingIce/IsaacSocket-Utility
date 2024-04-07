#include <render.hpp>
#include <imgui/imgui.h>
namespace render {
    void Render() {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("##IsaacSocket_Window", nullptr, flags);
        ImGui::Button("button");
        ImGui::End();
    }
}