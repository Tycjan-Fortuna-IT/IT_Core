#include "pch.hpp"
#include "Platform/GUI/Core/OpenGL/OpenGLContext.hpp"

#include "Engine/Core/Debug/Logger.hpp"

namespace Core {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        :m_WindowHandle(windowHandle) {
        ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::Init() {
        CORE_TRACE("Initializing OpenGL context for window");

        glfwMakeContextCurrent(m_WindowHandle);

        const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

        ASSERT(status, "Could not initialize GLAD!")
        ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Engine requires at least OpenGL version 4.5!")

        CORE_INFO("OpenGL Info:");
        CORE_INFO("  Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        CORE_INFO("  Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        CORE_INFO("  Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
        CORE_INFO("  GLSL Version: {}", reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
        CORE_INFO("  OpenGL Context Initialized!");
        CORE_INFO("  OpenGL Version: {}.{}", GLVersion.major, GLVersion.minor);
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}
