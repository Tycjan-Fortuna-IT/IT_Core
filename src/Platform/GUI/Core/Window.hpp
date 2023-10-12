#pragma once

#include <functional>
#include <memory>

#include "Engine/Core/Events/Event.hpp"
#include "OpenGL/OpenGLContext.hpp"

namespace Core {

    struct WindowProps final {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title, uint32_t width, uint32_t height)
            : Title(title), Width(width), Height(height) {}
    };

    class Window final {
    public:

        Window(const WindowProps& props);
        ~Window();

        void OnUpdate() const;

        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }

        void SetEventCallback(const std::function<void(Event&)>& callback) { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);

        bool IsMaximized() const { return glfwGetWindowAttrib(m_NativeWindow, GLFW_MAXIMIZED); }
        void Minimize();
        void Maximize();
        void Restore();

        void RegisterOverTitlebar(bool value);

        GLFWwindow* GetNativeWindow() const { return m_NativeWindow; }

    private:

        GLFWwindow* m_NativeWindow{ nullptr };

        std::shared_ptr<OpenGLContext> m_GraphicsContext;

        struct WindowData final {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            bool OverTitlebar = false;

            std::function<void(Event&)> EventCallback;
        };

        WindowData m_Data;
    };

}
