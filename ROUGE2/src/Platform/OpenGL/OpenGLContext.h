#pragma once

#include "ROUGE2/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace ROUGE2 {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}