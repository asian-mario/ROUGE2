#include "r2pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace ROUGE2 {
	Shader* Shader::Create(const std::string& filepath){
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    R2_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(filepath);
		}

		R2_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc){
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    R2_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		R2_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}