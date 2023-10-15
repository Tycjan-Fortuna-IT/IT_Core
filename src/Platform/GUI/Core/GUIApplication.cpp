#include "pch.hpp"
#include "GUIApplication.hpp"

#include "Engine/Core/Debug/Logger.hpp"

namespace Core {
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification(specification) {

        ASSERT(!s_Instance, "Application already exists!")
        CORE_TRACE("Creating application...");

        s_Instance = this;

        m_Window = std::make_shared<Window>(WindowProps{
            m_Specification.Name,
            m_Specification.Width,
            m_Specification.Height
        });

        m_Window->SetEventCallback(BIND_FN(Application::OnEvent));

        m_Window->SetVSync(true);

        m_GuiLayer = new ImGuiLayer();
        m_GuiLayer->OnAttach();
    }

    Application::~Application() {

    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {
            return OnWindowClose(e);
        });

        dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) {
            return OnWindowResize(e);
        });

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
            if (event.IsHandled)
                break;

            (*it)->OnEvent(event);
        }
    }

    void Application::Run() {
        while (m_Running) {
            m_Window->OnUpdate();

            const float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate(timestep);
            }

            m_GuiLayer->Begin();

            for (Layer* layer : m_LayerStack)
                layer->OnGuiRender();

            m_GuiLayer->End();
        }
    }

    void Application::Close() {
        m_Running = false;
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);

        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);

        overlay->OnAttach();
    }

    void Application::PopLayer(Layer* layer) {
        m_LayerStack.PopLayer(layer);
        layer->OnDetach();
    }

    void Application::PopOverlay(Layer* overlay) {
        m_LayerStack.PopOverlay(overlay);

        overlay->OnDetach();
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {

        return false;
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;

        return true;
    }
}

