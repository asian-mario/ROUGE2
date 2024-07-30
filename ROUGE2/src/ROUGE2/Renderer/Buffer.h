#pragma once

#include <vector>
namespace ROUGE2 {

	enum class ShaderDataType : uint8_t {
		None = 0, Vec, Vec2, Vec3, Vec4, Mat3, Mat4, VecInt, VecInt2, VecInt3, VecInt4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Vec:    return 4;
			case ShaderDataType::Vec2:   return 4 * 2;
			case ShaderDataType::Vec3:   return 4 * 3;
			case ShaderDataType::Vec4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::VecInt:      return 4;
			case ShaderDataType::VecInt2:     return 4 * 2;
			case ShaderDataType::VecInt3:     return 4 * 3;
			case ShaderDataType::VecInt4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		R2_CORE_ASSERT(false, "Unknown ShaderData Type");
		return 0;
	}
	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t offset;
		uint32_t size;
		bool normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const {
			switch (type) {
			case ShaderDataType::Vec:   return 1;
			case ShaderDataType::Vec2:  return 2;
			case ShaderDataType::Vec3:  return 3;
			case ShaderDataType::Vec4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::VecInt:     return 1;
			case ShaderDataType::VecInt2:    return 2;
			case ShaderDataType::VecInt3:    return 3;
			case ShaderDataType::VecInt4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}
			R2_CORE_ASSERT(false, "Unknown Shader Data Type");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}
		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }


	private:
		inline void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.offset = offset;
				offset += element.size;
				m_Stride += element.size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);
	};
}
