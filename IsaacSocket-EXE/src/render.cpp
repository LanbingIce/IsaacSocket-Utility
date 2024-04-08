#include <render.hpp>
#include <utils.hpp>
#include <imgui/imgui.h>
namespace render_ {
    bool show_demo_window = true;
    bool show_another_window = false;
    bool Render() {
        bool open = true; 
        
        ImGui::Begin("##IsaacSocket_Window", &open);
        if (ImGui::Button("button"))
        {
            mb("hello");
        }
        
        ImGui::End();
        return !open;
    }
}