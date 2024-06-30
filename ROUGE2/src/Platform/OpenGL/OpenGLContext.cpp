#include "r2pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace ROUGE2 {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		R2_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init(){
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		R2_CORE_ASSERT(status, "Failed to initialize Glad!");

		R2_CORE_LOG_INFO("OpenGL Info:");
		R2_CORE_LOG_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		R2_CORE_LOG_INFO("  Renderer: {0}", (const char*) glGetString(GL_RENDERER));
		R2_CORE_LOG_INFO("  Version: {0}", (const char*) glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers(){

		glfwSwapBuffers(m_WindowHandle);
	}

}