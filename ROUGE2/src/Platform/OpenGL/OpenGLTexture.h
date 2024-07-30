#pragma once

#include "ROUGE2/Renderer/Texture.h"

#include <glad/glad.h>
namespace ROUGE2 {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path, bool isLinear);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return m_Width; };
		virtual uint32_t getHeight() const override { return m_Height; };

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void SetLinear(bool linear) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		uint32_t m_Width, m_Height;
		std::string m_Path;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}