#include "r2pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace ROUGE2 {
	Ref<VertexArray> VertexArray::Create(){
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    R2_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}

		R2_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}