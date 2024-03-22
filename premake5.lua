workspace "MyView"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder {solution directory}
IncludeDir = {}
IncludeDir["GLFW"] = "MyView/vendor/GLFW/include"
IncludeDir["Glad"] = "MyView/vendor/Glad/include"
IncludeDir["ImGui"] = "MyView/vendor/imgui"
IncludeDir["glm"] = "MyView/vendor/glm"

include "MyView/vendor/GLFW"
include "MyView/vendor/Glad"
include "MyView/vendor/ImGui"

project "MyView"
	location "MyView"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mvpch.h"
	pchsource "MyView/src/mvpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
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
		"opengl32.lib",
		"dwmapi.lib"
	}

	libdirs 
	{
		"vendor/GLFW/lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"MV_PLATFORM_WINDOWS",
			"MV_BUILD_STATIC",
			"GLFW_INCLUDE_NONE",
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
		}

	filter "configurations:Debug"
		defines "MV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MV_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"MyView/vendor/spdlog/include",
		"MyView/src",
		"MyView/vendor",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"MV_PLATFORM_WINDOWS",
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
		}
		
		links
		{
			"MyView",
			"ImGui"
		}

	filter "configurations:Debug"
		defines "MV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MV_DIST"
		runtime "Release"
		optimize "on"