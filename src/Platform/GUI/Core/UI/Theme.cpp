#include "pch.hpp"
#include "Theme.hpp"

#include <icons/IconsMaterialDesignIcons.h>
#include <icons/MaterialDesign.inl>

namespace Core {
	ImFont* Theme::DefaultFont = nullptr;
    ImFont* Theme::SmallFont = nullptr;
    ImFont* Theme::BoldFont = nullptr;

    static void AddIconFont(float fontSize) {
        ImGuiIO& io = ImGui::GetIO();

        static constexpr ImWchar icons_ranges[] = { ICON_MIN_MDI, ICON_MAX_MDI, 0 };
        ImFontConfig iconsConfig;
        // merge in icons from Font Awesome
        iconsConfig.MergeMode = true;
        iconsConfig.PixelSnapH = true;
        iconsConfig.GlyphOffset.y = 1.0f;
        iconsConfig.OversampleH = iconsConfig.OversampleV = 1;
        iconsConfig.GlyphMinAdvanceX = 4.0f;
        iconsConfig.SizePixels = 12.0f;

        io.Fonts->AddFontFromMemoryCompressedTTF(MaterialDesign_compressed_data, MaterialDesign_compressed_size, fontSize, &iconsConfig, icons_ranges);
    }

    void Theme::SetFont() {
		ImGuiIO& io = ImGui::GetIO();
		float fontSize = 32.0f;
		float fontSizeSmall = 12.0f;

		ImFontConfig iconsConfig;
        iconsConfig.MergeMode = false;
        iconsConfig.PixelSnapH = true;
        iconsConfig.OversampleH = iconsConfig.OversampleV = 1;
        iconsConfig.GlyphMinAdvanceX = 4.0f;
        iconsConfig.SizePixels = 12.0f;

		constexpr const char* regularFontPath	= "assets/fonts/jetbrains-mono/JetBrainsMono-Regular.ttf";
		constexpr const char* boldFontPath		= "assets/fonts/jetbrains-mono/JetBrainsMono-Bold.ttf";

		DefaultFont = io.Fonts->AddFontFromFileTTF(regularFontPath, fontSize, &iconsConfig);
		AddIconFont(fontSize);
		SmallFont = io.Fonts->AddFontFromFileTTF(regularFontPath, fontSizeSmall, &iconsConfig);
		AddIconFont(fontSizeSmall);

		BoldFont = io.Fonts->AddFontFromFileTTF(boldFontPath, fontSize, &iconsConfig);
		AddIconFont(fontSize);

		io.Fonts->TexGlyphPadding = 1;
        for (int n = 0; n < io.Fonts->ConfigData.Size; n++) {
            ImFontConfig* fontConfig = &io.Fonts->ConfigData[n];
            fontConfig->RasterizerMultiply = 1.0f;
        }
		io.Fonts->Build();
	}
}
