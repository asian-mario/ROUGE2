#pragma once

#include "r2pch.h"
#include "Core.h"
#include "Events/Event.h"

namespace ROUGE2 {

	class ROUGE2_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//def. in client
	Application* CreateApplication();
}

