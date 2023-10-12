#pragma once

#include "Engine/Core/Layer.hpp"
#include "Platform/GUI/Core/Timestep.hpp"

namespace Core {
    class ImGuiLayer final : public Layer {
    public:

        ImGuiLayer();
        ~ImGuiLayer() override = default;

        auto OnAttach() -> void override;
        auto OnDetach() -> void override;

        auto OnUpdate(Timestep dt) -> void override;
        auto OnEvent(Event& event) -> void override;

        auto OnGuiRender() -> void override;

        auto Begin() const -> void;
        auto End() const -> void;

        auto SetBlockEvents(bool block) -> void { m_BlockEvents = block; }

    private:

        bool m_BlockEvents = true;
    };
}
