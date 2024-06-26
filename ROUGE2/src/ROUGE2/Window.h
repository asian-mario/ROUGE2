#pragma once

#include "r2pch.h"

#include "ROUGE2/Core.h"
#include "ROUGE2/Events/Event.h"

namespace ROUGE2 {
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "ROUGE2 Engine",
			unsigned int width = 1280,
			unsigned int height = 860)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class ROUGE2_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//atr.
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps()); //has to be defined i. cpp for each platform
 	};
}