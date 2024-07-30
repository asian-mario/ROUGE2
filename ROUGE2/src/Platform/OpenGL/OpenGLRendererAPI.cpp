#include "r2pch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

void ROUGE2::OpenGLRendererAPI::Init(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void ROUGE2::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height){
	glViewport(x, y, width, height);
}

void ROUGE2::OpenGLRendererAPI::SetClearColor(const glm::vec4& color){
	glClearColor(color.r, color.g, color.b, color.a);
}

void ROUGE2::OpenGLRendererAPI::Clear(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ROUGE2::OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount	){
	uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);
}
