#include "mvpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "MyView/Core.h"
#include "MyView/Log.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace MyView {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: MV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }
        MV_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None: MV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
        }
        MV_CORE_ASSERT(false, "Unkown RendererAPI!");
        return nullptr;
    }
}