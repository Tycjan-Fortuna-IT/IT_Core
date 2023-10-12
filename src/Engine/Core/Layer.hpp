#pragma once
#include <string>

#include "Engine/Core/Events/Event.hpp"
#include "Platform/GUI/Core/Timestep.hpp"

namespace Core {
    class Layer {
    public:

        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}

        virtual void OnUpdate(Timestep dt) {}
        virtual void OnEvent(Event& event) {}

        virtual void OnGuiRender() {}

        const std::string& GetName() { return m_Name; }

    private:

        std::string m_Name;
    };
}
