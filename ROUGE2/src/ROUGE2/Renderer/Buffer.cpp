#include "r2pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace ROUGE2 {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
		switch (Renderer::GetAPI()) {
		case RendererAPI::None: 
			R2_CORE_ASSERT(false, "RendererAPI::None is currently not supported or there is no API!");
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		R2_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			R2_CORE_ASSERT(false, "RendererAPI::None is currently not supported or there is no API!");
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		R2_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}