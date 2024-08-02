#include "r2pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace ROUGE2 {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) //temp will be moved
	{
		switch (type)
		{
		case ROUGE2::ShaderDataType::Vec:    return GL_FLOAT;
		case ROUGE2::ShaderDataType::Vec2:   return GL_FLOAT;
		case ROUGE2::ShaderDataType::Vec3:   return GL_FLOAT;
		case ROUGE2::ShaderDataType::Vec4:   return GL_FLOAT;
		case ROUGE2::ShaderDataType::Mat3:     return GL_FLOAT;
		case ROUGE2::ShaderDataType::Mat4:     return GL_FLOAT;
		case ROUGE2::ShaderDataType::VecInt:      return GL_INT;
		case ROUGE2::ShaderDataType::VecInt2:     return GL_INT;
		case ROUGE2::ShaderDataType::VecInt3:     return GL_INT;
		case ROUGE2::ShaderDataType::VecInt4:     return GL_INT;
		case ROUGE2::ShaderDataType::Bool:     return GL_BOOL;
		}

		R2_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray(){
		OSVI_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray(){
		OSVI_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const{
		OSVI_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const{
		OSVI_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		OSVI_PROFILE_FUNCTION();

		R2_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.type)
			{
			case ShaderDataType::Vec:
			case ShaderDataType::Vec2:
			case ShaderDataType::Vec3:
			case ShaderDataType::Vec4:
			case ShaderDataType::VecInt:
			case ShaderDataType::VecInt2:
			case ShaderDataType::VecInt3:
			case ShaderDataType::VecInt4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++){
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				R2_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer){
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}