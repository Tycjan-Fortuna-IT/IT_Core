#pragma once
#include "pch.hpp"

#include "imgui.h"
#include "imgui_internal.h"

namespace Core {

    class ScopedColor {
    public:
        template<typename T>
        ScopedColor(ImGuiCol colourId, T colour) { ImGui::PushStyleColor(colourId, ImColor(colour).Value); }

        ScopedColor(const ScopedColor&) = delete;

        ~ScopedColor() { ImGui::PopStyleColor(); }

        ScopedColor& operator=(const ScopedColor&) = delete;
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

        template<typename T>
        ScopedStyle(ImGuiStyleVar style, T value) { ImGui::PushStyleVar(style, value); }

        ScopedStyle(const ScopedStyle& other) = delete;

        ~ScopedStyle() { ImGui::PopStyleVar(); }

        ScopedStyle& operator=(const ScopedStyle& other) = delete;
    }; 

    class ScopedID {
    public:

        template<typename T>
        ScopedID(T id) { ImGui::PushID(id); }

        ScopedID(const ScopedID& other) = delete;

        ~ScopedID() { ImGui::PopID(); }

        ScopedID& operator=(const ScopedID& other) = delete;
    };

    namespace UI {

        inline void ShiftCursorX(float distance) {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + distance);
        }

        inline void ShiftCursorY(float distance) {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + distance);
        }

        inline void ShiftCursor(float x, float y) {
            const ImVec2 cursor = ImGui::GetCursorPos();

            ImGui::SetCursorPos(ImVec2(cursor.x + x, cursor.y + y));
        }

        inline bool IsItemDisabled() {
            return ImGui::GetItemFlags() & ImGuiItemFlags_Disabled;
        }

        inline bool PropertyDropdown(const char* label, const char** options, int32_t optionCount, int32_t* selected) {
            const char* current = options[*selected];

            ShiftCursor(10.0f, 9.0f);
            ImGui::Text(label);
            ImGui::NextColumn();
            ShiftCursorY(4.0f);
            ImGui::PushItemWidth(-1);

            bool modified = false;

            const std::string id = "##" + std::string(label);

            if (ImGui::BeginCombo(id.c_str(), current)) {
                for (int i = 0; i < optionCount; i++) {
                    const bool is_selected = (current == options[i]);
                    if (ImGui::Selectable(options[i], is_selected)) {
                        current = options[i];
                        *selected = i;
                        modified = true;
                    }

                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            ImGui::PopItemWidth();
            ImGui::NextColumn();

            return modified;
        }
    }
}
