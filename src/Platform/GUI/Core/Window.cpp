#include "pch.hpp"
#include "Platform/GUI/Core/Window.hpp"

#include "Engine/Core/Debug/Logger.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

namespace Core {
    static bool s_GLFWInitialized = false;

    Window::Window(const WindowProps& props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        CORE_TRACE("Creating window: " + props.Title + " " + std::to_string(props.Width) + "x" + std::to_string(props.Height));

        if (!s_GLFWInitialized) {
            const int success = glfwInit();

            ASSERT(success, "Could not initialize GLFW!")

            s_GLFWInitialized = true;
        }

        //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_TITLEBAR, GLFW_FALSE);

        m_NativeWindow = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(), nullptr, nullptr);

        m_GraphicsContext = std::make_shared<OpenGLContext>(m_NativeWindow);

        m_GraphicsContext->Init();

        glfwSetWindowUserPointer(m_NativeWindow, &m_Data);

        SetVSync(true);

        glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* window) {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(static_cast<KeyCode>(key));
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods) {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xPos, double yPos) {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            data.EventCallback(event);
        });

        glfwSetCharCallback(m_NativeWindow, [](GLFWwindow* window, unsigned int keycode) {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            KeyTypedEvent event(static_cast<KeyCode>(keycode));
            data.EventCallback(event);
        });

#ifdef CORE_PLATFORM_WINDOWS
        glfwSetTitlebarHitTestCallback(m_NativeWindow, [](GLFWwindow* window, [[maybe_unused]] int xPos, [[maybe_unused]] int yPos, int* hit) {
            *hit = static_cast<WindowData*>(glfwGetWindowUserPointer(window))->OverTitlebar ? 1 : 0;
        });
#endif
    }

    Window::~Window() {
        glfwDestroyWindow(m_NativeWindow);
    }

    void Window::OnUpdate() const {
        glfwPollEvents();
        glfwSwapBuffers(m_NativeWindow);
    }

    void Window::SetVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    void Window::Minimize() {
        glfwIconifyWindow(m_NativeWindow);
    }

    void Window::Maximize() {
        glfwMaximizeWindow(m_NativeWindow);
    }

    void Window::Restore() {
        glfwRestoreWindow(m_NativeWindow);
    }

    void Window::RegisterOverTitlebar(bool value) {
        m_Data.OverTitlebar = value;
    }
}
