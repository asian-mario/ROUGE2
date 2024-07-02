#pragma once
#include "RenderCommand.h"

namespace ROUGE2 {

	class Renderer {
	public:
		static void BeginScene(); // take scene params later
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}