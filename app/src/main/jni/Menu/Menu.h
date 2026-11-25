#ifndef MENU
#define MENU
#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>

namespace Menu {
    bool init = false;
    bool esp_box = true, esp_skeleton = false, silent_aim = false, no_recoil = false;
    float aim_fov = 15.0f;

    void Setup() {
        ImGui::CreateContext();
        ImGui_ImplAndroid_Init(NULL);
        ImGui_ImplOpenGL3_Init("#version 300 es");
        ImGui::StyleColorsDark();
        ImGui::GetStyle().ScaleAllSizes(3.0f);
    }

    void Draw() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("XENZETCU");
        if (ImGui::BeginTabBar("Tabs")) {
            if (ImGui::BeginTabItem("Visual")) {
                ImGui::Checkbox("ESP Box", &esp_box);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Legit")) {
                ImGui::Checkbox("Silent Aim", &silent_aim);
                ImGui::SliderFloat("FOV", &aim_fov, 1.0f, 180.0f);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Misc")) {
                ImGui::Checkbox("No Recoil", &no_recoil);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
#endif
