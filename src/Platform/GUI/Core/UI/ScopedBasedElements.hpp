#pragma once
#include "pch.hpp"

#include "Platform/GUI/Core/UI/Color.hpp"

namespace Core {

    // Color
    class ScopedColor {
    public:

        ScopedColor(ImGuiCol_ element, ImU32 color) {
            ImGui::PushStyleColor(element, color);
        }

        ~ScopedColor() { ImGui::PopStyleColor(); }

    };

    // Font
    class ScopedFont {
    public:

        ScopedFont(int index) {
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[index]);
        }

        ~ScopedFont() { ImGui::PopFont(); }

    };

    // Style
    class ScopedStyle {
    public:

        template <typename T>
        ScopedStyle(ImGuiStyleVar_ element, T value) {
            ImGui::PushStyleVar(element, value);
        }

        ~ScopedStyle() { ImGui::PopStyleVar(); }
    }; 

    // ID
    class ScopedID {
    public:

        ScopedID(int value) { ImGui::PushID(value); }

        ~ScopedID() { ImGui::PopID(); }
    };
}
