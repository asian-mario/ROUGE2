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

	#ifdef R2_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		R2_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "R2 requires at least OpenGL version 4.5!");
	#endif

	void OpenGLContext::SwapBuffers(){

		glfwSwapBuffers(m_WindowHandle);
	}

}