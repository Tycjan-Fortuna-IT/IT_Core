#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Core {
    class OpenGLContext final {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        ~OpenGLContext() = default;

        void Init();

        void SwapBuffers();

    private:
        GLFWwindow* m_WindowHandle;
    };
}
