#pragma once

namespace Core {
    class Timestep final {
    public:

        Timestep() = default;

        Timestep(float time = 0.0f)
            : m_Time(time) {}

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMiliseconds() const { return m_Time * 1000.f; }

    private:

        float m_Time;
    };
}
