#pragma once
#include "RenderCommand.h"

#include "OrthoCamera.h"
#include "Shader.h"

namespace ROUGE2 {

	class Renderer {
	public:
		static void BeginScene(OrthoCamera& camera); // take scene params later
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjMatrix;
		};

		static SceneData* m_SceneData;
	};
}