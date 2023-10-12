#pragma once

#include "Engine/Core/Events/Event.hpp"
#include "Platform/GUI/Core/KeyCode.hpp"

namespace Core {
    class KeyEvent : public Event {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        DECLARE_EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(KeyCode keyCode)
            : m_KeyCode(keyCode) {}

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(const KeyCode keycode, bool repeat = false)
            : KeyEvent(keycode), m_IsRepeat(repeat) {}

        DECLARE_EVENT_TYPE(KeyPressed)

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(static_cast<int>(m_KeyCode)) +
                " (repeat = " + std::to_string(m_IsRepeat) + ")";
        }

    private:

        bool m_IsRepeat;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        DECLARE_EVENT_TYPE(KeyReleased)

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(static_cast<int>(m_KeyCode));
        }
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        DECLARE_EVENT_TYPE(KeyTyped)

        std::string ToString() const override {
            return std::string(GetName()) + ": " + std::to_string(static_cast<int>(m_KeyCode));
        }
    };
}
