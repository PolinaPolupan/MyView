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
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"MV_PLATFORM_WINDOWS",
			"MV_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "MV_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MV_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MV_DIST"
		buildoptions "/MD"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "off"

	language "C++"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"MV_PLATFORM_WINDOWS"
		}
		
		links
		{
			"MyView",
			"ImGui"
		}

	filter "configurations:Debug"
		defines "MV_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MV_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MV_DIST"
		runtime "Release"
		optimize "On"