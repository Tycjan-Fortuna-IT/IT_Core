#pragma once
#include <string>

#define BIT(x) (1 << (x))

#define BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define DECLARE_EVENT_TYPE(type) \
        static EventType GetStaticType() { return EventType::type; } \
        virtual EventType GetType() const override { return GetStaticType(); } \
        virtual const char* GetName() const override { return #type; }

#define DECLARE_EVENT_CATEGORY(category) \
        virtual int GetCategoryFlags() const override { return category; }

namespace Core {

    enum class EventType : int {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory : int {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput =       BIT(1),
        EventCategoryKeyboard =    BIT(2),
        EventCategoryMouse =       BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    class Event {
    public:

        virtual ~Event() = default;

        bool IsHandled = false;

        virtual const char* GetName() const = 0;

        virtual EventType GetType() const = 0;

        virtual int GetCategoryFlags() const = 0;

        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher final {
    public:

        EventDispatcher(Event& event)
            : m_Event(event) {}

        template <typename T, typename Fn>
        requires std::invocable<Fn, T&> && std::is_base_of<Event, T>::value
        bool Dispatch(const Fn& fn) {
            if (m_Event.GetType() == T::GetStaticType()) {
                m_Event.IsHandled = fn((T&)m_Event);

                return true;
            }

            return false;
        }

    private:
        Event& m_Event;
    };

}
