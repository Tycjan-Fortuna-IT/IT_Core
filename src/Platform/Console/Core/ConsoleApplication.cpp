#include "pch.hpp"
#include "ConsoleApplication.hpp"

#include "Engine/Core/Debug/Logger.hpp"

namespace Core {
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification(specification) {

        ASSERT(!s_Instance, "Application already exists!")
        CORE_TRACE("Creating application...");

        s_Instance = this;
    }

    Application::~Application() {
        
    }

    void Application::Run() {
        for (Layer* layer : m_LayerStack) {
            layer->OnAttach();
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }
}
