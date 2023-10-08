#include "pch.hpp"
#include "ConsoleApplication.hpp"

namespace Core {
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& name)
        : m_Name(name) {
        
    }

    void Application::Run() {

    }
}
