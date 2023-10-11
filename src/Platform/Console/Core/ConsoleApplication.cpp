#include "pch.hpp"
#include "ConsoleApplication.hpp"

#include "Engine/Core/Debug/Logger.hpp"

namespace Core {
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification(specification) {

        ASSERT(!s_Instance, "Application already exists!");
        CORE_TRACE("Creating application...");

        s_Instance = this;

    }

    void Application::Run() {

    }

    void Application::Close() {

    }
}
