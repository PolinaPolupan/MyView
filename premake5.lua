workspace "MyView"
	architecture "x64"

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

include "MyView/vendor/GLFW"

project "MyView"
	location "MyView"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mvpch.h"
	pchsource "MyView/src/mvpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"MV_PLATFORM_WINDOWS",
			"MV_BUILD_DLL"
		}
		postbuildcommands
		{
			"{RMDIR} ../bin/" .. outputdir .. "/Sandbox",
			"{MKDIR} ../bin/" .. outputdir .. "/Sandbox",
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		}

	filter "configurations:Debug"
		defines "MV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MV_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MyView/vendor/spdlog/include",
		"MyView/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"MV_PLATFORM_WINDOWS"
		}
		
		links
		{
			"MyView"
		}

	filter "configurations:Debug"
		defines "MV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MV_DIST"
		optimize "On"