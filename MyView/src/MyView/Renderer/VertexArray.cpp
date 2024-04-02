#include "mvpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace MyView {

	VertexArray* MyView::VertexArray::Create()
	{
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None: MV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL: return new OpenGLVertexArray();
        }
        MV_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
	}
}

