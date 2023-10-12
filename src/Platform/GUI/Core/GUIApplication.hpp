#pragma once

#include <string>

#include "Window.hpp"
#include "Engine/Core/LayerStack.hpp"
#include "Events/ApplicationEvent.hpp"
#include "UI/ImGuiLayer.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv);

namespace Core {
    enum class ApplicationType {
        Window,
        Console
    };

    struct ApplicationCommandArguments final {
        int Argc{ 0 };
        char** Argv{ nullptr };
    };

    struct ApplicationSpecification final {
        std::string Name{ "Core Application" };
        ApplicationType Type{ ApplicationType::Window };
        uint32_t Width{ 0 }; // If Type is Window, Width and Height are required
        uint32_t Height{ 0 };
        ApplicationCommandArguments CommandArguments; // If Type is Console, CommandArguments are required
    };

    class Application {
    public:
        explicit Application(const ApplicationSpecification& specification);
        virtual ~Application();

        Application(const Application& other) = delete;
        Application(Application&& other) = delete;

        virtual void OnUpdate(Timestep dt) {}
        virtual void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        const ApplicationSpecification& GetSpecification() const { return m_Specification; }
        bool IsRunning() const { return m_Running; }

        void Close();

        static Application& Get() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }

        auto GetGuiLayer() const -> ImGuiLayer* { return m_GuiLayer; }

    protected:

        ApplicationSpecification m_Specification;
        bool m_Running{ true };

    private:
        void Run();

        static Application* s_Instance;

        float m_LastFrameTime = 0.0f;

        LayerStack m_LayerStack;

        std::shared_ptr<Window> m_Window{ nullptr };
        ImGuiLayer* m_GuiLayer{ nullptr };

        auto OnWindowResize(WindowResizeEvent& e) -> bool;
        auto OnWindowClose(WindowCloseEvent& e) -> bool;

        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication([[maybe_unused]] int argc, [[maybe_unused]] char** argv);
}
