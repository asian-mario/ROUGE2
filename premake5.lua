workspace "ROUGE2"
	architecture "x64"

	configurations{
		"Debug", 
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ROUGE2/vendor/GLFW/include"

include "ROUGE2/vendor/GLFW"

project "ROUGE2"
	location "ROUGE2"
	kind "SharedLib" --.dll
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "r2pch.h"
	pchsource "ROUGE2/src/r2pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"R2_PLATFORM_WINDOWS",
			"R2_BUILD_DLL"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "R2_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "R2_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "R2_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"ROUGE2/vendor/spdlog/include",
		"ROUGE2/src"
	}

	links{
		"ROUGE2"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"R2_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "R2_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "R2_RELEASE"
		optimize "On"

	filter "configurations:Debug"
		defines "R2_DIST"
		optimize "On"