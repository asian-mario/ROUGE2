#pragma once

#include "Core.h"

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

