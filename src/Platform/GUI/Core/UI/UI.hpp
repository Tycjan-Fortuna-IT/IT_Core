#pragma once
#include "pch.hpp"

#include "Platform/GUI/Core/UI/Color.hpp"

namespace Core {

    class ScopedColor {
    public:

        ScopedColor(ImGuiCol_ element, ImU32 color) {
            ImGui::PushStyleColor(element, color);
        }

        ScopedColor(const ScopedColor& other) = delete;
        
        ~ScopedColor() { ImGui::PopStyleColor(); }

        ScopedColor& operator=(const ScopedColor& other) = delete;
    };

    class ScopedFont {
    public:

        ScopedFont(ImFont* font) { ImGui::PushFont(font); }

        ScopedFont(const ScopedFont& other) = delete;

        ~ScopedFont() { ImGui::PopFont(); }

        ScopedFont& operator=(const ScopedFont& other) = delete;
    };

    class ScopedStyle {
    public:

        template <typename T>
        ScopedStyle(ImGuiStyleVar_ element, T value) {
            ImGui::PushStyleVar(element, value);
        }

        ScopedStyle(const ScopedStyle& other) = delete;

        ~ScopedStyle() { ImGui::PopStyleVar(); }

        ScopedStyle& operator=(const ScopedStyle& other) = delete;
    }; 

    class ScopedID {
    public:

        ScopedID(int value) { ImGui::PushID(value); }

        ScopedID(const ScopedID& other) = delete;

        ~ScopedID() { ImGui::PopID(); }

        ScopedID& operator=(const ScopedID& other) = delete;
    };
}
