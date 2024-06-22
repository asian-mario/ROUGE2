#include "r2pch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "ROUGE2/Log.h"

#include <GLFW/glfw3.h>

namespace ROUGE2 {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}