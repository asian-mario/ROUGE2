#include "r2pch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "ROUGE2/Log.h"

namespace ROUGE2 {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1920, 1080);
		if (e.IsInCategory(EventCategoryApplication)) {
			R2_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput)) { //test to see if it identifies category correctly
			R2_TRACE(e);
		}

		while (true);
	}
}