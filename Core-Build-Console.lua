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
        "CORE_CONSOLE_BUILD",
        "SPDLOG_COMPILED_LIB",
        "_CRT_SECURE_NO_WARNINGS",
        "ENABLE_ASSERTS",
    }

    files {
        "src/Engine/**.hpp",
        "src/Engine/**.cpp",

        "src/Core.hpp",

        "src/pch.hpp",
        "src/pch.cpp",

        "src/Platform/Console/**.hpp",
        "src/Platform/Console/**.cpp",
    }

    includedirs {
        "src"
    }

    externalincludedirs {
        "%{IncludeDir.SPDLOG}"
    }

    links {
        "spdlog"
    }

    libdirs {
        "%{LibDir.SPDLOG}"
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
    group ""
