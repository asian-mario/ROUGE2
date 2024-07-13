#include "r2pch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
namespace ROUGE2 {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	void Renderer::Init(){
		RenderCommand::Init();
	}
	void Renderer::BeginScene(OrthoCamera& camera){
		m_SceneData->ViewProjMatrix = camera.GetViewProjMatrix();
	}

	void Renderer::EndScene(){

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform){
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProj", m_SceneData->ViewProjMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}