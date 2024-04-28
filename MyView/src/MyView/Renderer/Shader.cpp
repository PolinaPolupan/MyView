#include "mvpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace MyView {

    Shader* MyView::Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: MV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        MV_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Shader* Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: MV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
        }
        MV_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}