#include "pch.hpp"
#include "ImGuiLayer.hpp"

#include <icons/IconsMaterialDesignIcons.h>
#include <icons/MaterialDesign.inl>

#include "ImGuiGLFW.hpp"
#include "ImGuiOpenGL.hpp"
#include "GLFW/glfw3.h"
#include "Platform/GUI/Core/GUIApplication.hpp"

namespace Core {
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer") {}

    auto ImGuiLayer::OnAttach() -> void {
        IMGUI_CHECKVERSION();
        
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        Application& app = Application::Get();
        GLFWwindow* window = app.GetWindow().GetNativeWindow();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    auto ImGuiLayer::OnDetach() -> void {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    auto ImGuiLayer::OnUpdate(Timestep dt) -> void {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));
        io.DeltaTime = dt.GetSeconds();
    }

    auto ImGuiLayer::OnEvent(Event& event) -> void {
        if (m_BlockEvents) {
            ImGuiIO& io = ImGui::GetIO();
            event.IsHandled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
            event.IsHandled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }

    auto ImGuiLayer::OnGuiRender() -> void {

    }

    auto ImGuiLayer::Begin() const -> void {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    auto ImGuiLayer::End() const -> void {
        ImGuiIO& io = ImGui::GetIO();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

}
