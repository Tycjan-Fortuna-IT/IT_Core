project "Core"
    kind "StaticLib"

    language "C++"
    cppdialect "C++20"

    staticruntime "off"

    externalwarnings "off"

    flags {}

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.hpp"
	pchsource "src/pch.cpp"

    defines {
        "CORE_GUI_BUILD",
        "SPDLOG_COMPILED_LIB",
        "GLFW_INCLUDE_NONE",
        "IMGUI_DEFINE_MATH_OPERATORS",
        "_CRT_SECURE_NO_WARNINGS",
    }

    files {
        "src/Engine/**.hpp",
        "src/Engine/**.cpp",

        "src/Core.hpp",

        "src/pch.hpp",
        "src/pch.cpp",

        "src/Platform/GUI/**.hpp",
        "src/Platform/GUI/**.cpp",
    }

    includedirs {
        "src"
    }

    externalincludedirs {
        "%{IncludeDir.SPDLOG}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGui}",
    }

    links {
        "spdlog",
        "GLFW",
        "GLAD",
    }

    libdirs {
        "%{LibDir.SPDLOG}",
        "%{LibDir.GLAD}",
        "%{LibDir.GLFW}",
    }

    postbuildcommands {}

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        pic "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines "CORE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "CORE_RELEASE"
        runtime "Release"
        symbols "on"
        optimize "speed"

    filter "configurations:Dist"
        defines "CORE_DIST"
        runtime "Release"
        symbols "off"
        optimize "speed"

    group "Dependencies"
        include "Core/vendor/spdlog"
        include "Core/vendor/GLAD"
        include "Core/vendor/GLFW"
    group ""
