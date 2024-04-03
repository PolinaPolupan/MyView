#include "mvpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace MyView {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}