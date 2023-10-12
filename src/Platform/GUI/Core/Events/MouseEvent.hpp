#pragma once

#include "Engine/Core/Events/Event.hpp"
#include "Platform/GUI/Core/MouseCode.hpp"

namespace Core {
    class MouseMovedEvent : public Event {
    public:

        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        DECLARE_EVENT_TYPE(MouseMoved)
        DECLARE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(m_MouseX) + ", " + std::to_string(m_MouseY);
        }

    private:

        float m_MouseX;
        float m_MouseY;
    };

    class MouseScrolledEvent : public Event {
    public:

        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        DECLARE_EVENT_TYPE(MouseScrolled)
        DECLARE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(m_XOffset) + ", " + std::to_string(m_YOffset);
        }

    private:

        float m_XOffset;
        float m_YOffset;
    };

    class MouseButtonEvent : public Event {
    public:

        MouseCode GetMouseButton() const { return m_Button; }

        DECLARE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

    protected:

        MouseButtonEvent(MouseCode button)
            : m_Button(button) {}

        MouseCode m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:

        MouseButtonPressedEvent(MouseCode button)
            : MouseButtonEvent(button) {}

        DECLARE_EVENT_TYPE(MouseButtonPressed)

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(static_cast<int>(m_Button));
        }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:

        MouseButtonReleasedEvent(MouseCode button)
            : MouseButtonEvent(button) {}

        DECLARE_EVENT_TYPE(MouseButtonReleased)

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(static_cast<int>(m_Button));
        }
    };
}
