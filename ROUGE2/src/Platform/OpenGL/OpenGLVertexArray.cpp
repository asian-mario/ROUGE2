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
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray(){
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer){
		R2_CORE_ASSERT(vertexBuffer->GetLayout().GetElements.size(), "Vertex buffer has no layout"); //size 0 triggers assert

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type), element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer){
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}