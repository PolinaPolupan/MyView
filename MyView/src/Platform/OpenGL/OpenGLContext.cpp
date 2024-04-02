#include "mvpch.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "MyView/Core.h"
#include "MyView/Log.h"

namespace MyView {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MV_CORE_ASSERT(windowHandle, "Window doesn't exist!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MV_CORE_ASSERT(status, "Failed to initialize Glad");
		
		MV_CORE_INFO("OpenGL Info:");
		MV_CORE_INFO("   Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		MV_CORE_INFO("   Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		MV_CORE_INFO("   Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}