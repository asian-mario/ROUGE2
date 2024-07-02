#include "r2pch.h"
#include "Renderer.h"

namespace ROUGE2 {
	void Renderer::BeginScene(){

	}

	void Renderer::EndScene(){

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray){
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}