#pragma once

namespace ROUGE2 {
	enum class RendererAPI {
		None = 0, OpenGL = 1
	};
	/*
		future support: Vulkan, DX11/12
	*/

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}