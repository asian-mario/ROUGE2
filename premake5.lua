workspace "ROUGE2"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ROUGE2/vendor/GLFW/include"
IncludeDir["Glad"] = "ROUGE2/vendor/Glad/include"
IncludeDir["ImGui"] = "ROUGE2/vendor/imgui"
IncludeDir["glm"] = "ROUGE2/vendor/glm"

include "ROUGE2/vendor/GLFW"
include "ROUGE2/vendor/Glad"
include "ROUGE2/vendor/imgui"

workspace "ROUGE2"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ROUGE2/vendor/GLFW/include"
IncludeDir["Glad"] = "ROUGE2/vendor/Glad/include"
IncludeDir["ImGui"] = "ROUGE2/vendor/imgui"
IncludeDir["glm"] = "ROUGE2/vendor/glm"

include "ROUGE2/vendor/GLFW"
include "ROUGE2/vendor/Glad"
include "ROUGE2/vendor/imgui"

project "ROUGE2"
    location "ROUGE2"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "r2pch.h"
    pchsource "ROUGE2/src/r2pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links 
    { 
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest" -- Use a different SDK version if possible

        defines
        {
            "R2_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "R2_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "R2_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "R2_DIST"
        runtime "Release"
        optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ROUGE2/vendor/spdlog/include",
		"ROUGE2/src",
		"ROUGE2/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"ROUGE2"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"R2_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "R2_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "R2_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "R2_DIST"
		runtime "Release"
		optimize "on"