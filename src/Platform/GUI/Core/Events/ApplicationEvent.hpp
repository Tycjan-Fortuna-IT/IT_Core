#pragma once

#include "Engine/Core/Events/Event.hpp"

namespace Core {
    class WindowCloseEvent : public Event {
    public:

        WindowCloseEvent() = default;

        DECLARE_EVENT_TYPE(WindowClose)
        DECLARE_EVENT_CATEGORY(EventCategoryApplication)
    };

    class WindowResizeEvent : public Event {
    public:

        WindowResizeEvent(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height) {}

        DECLARE_EVENT_TYPE(WindowResize)
        DECLARE_EVENT_CATEGORY(EventCategoryApplication)

        std::string ToString() const override {
            return std::string(GetName()) + ". New resolution is: " + std::to_string(m_Width) + "x" + std::to_string(m_Height);
        }

    private:

        uint32_t m_Width;
        uint32_t m_Height;
    };
}
