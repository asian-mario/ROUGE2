#include "r2pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace ROUGE2 {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size){
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			R2_CORE_ASSERT(false, "Render	erAPI::None is currently not supported or there is no API!");
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		}

		R2_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size){
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: 
			R2_CORE_ASSERT(false, "RendererAPI::None is currently not supported or there is no API!");
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		R2_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size){
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			R2_CORE_ASSERT(false, "RendererAPI::None is currently not supported or there is no API!");
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		R2_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}