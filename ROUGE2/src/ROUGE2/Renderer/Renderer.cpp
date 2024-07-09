#include "r2pch.h"
#include "Renderer.h"

namespace ROUGE2 {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthoCamera& camera){
		m_SceneData->ViewProjMatrix = camera.GetViewProjMatrix();
	}

	void Renderer::EndScene(){

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform){
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProj", m_SceneData->ViewProjMatrix);
		shader->UploadUniformMat4("u_ModelMat", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}