#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace ROUGE2 {

	class ROUGE2_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//def. in client
	Application* CreateApplication();
}

