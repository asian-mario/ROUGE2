#include "r2pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

void ROUGE2::OpenGLRendererAPI::SetClearColor(const glm::vec4& color){
	glClearColor(color.r, color.g, color.b, color.a);
}

void ROUGE2::OpenGLRendererAPI::Clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ROUGE2::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray){
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
