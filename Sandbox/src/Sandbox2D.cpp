#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach(){
	m_SquareVA = ROUGE2::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	ROUGE2::Ref<ROUGE2::VertexBuffer> squareVB;
	squareVB.reset(ROUGE2::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ ROUGE2::ShaderDataType::Vec3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	ROUGE2::Ref<ROUGE2::IndexBuffer> squareIB;
	squareIB.reset(ROUGE2::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = ROUGE2::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach(){
}

void Sandbox2D::OnUpdate(ROUGE2::Timestep ts){
	m_CameraController.OnUpdate(ts);

	ROUGE2::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ROUGE2::RenderCommand::Clear();

	ROUGE2::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<ROUGE2::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<ROUGE2::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	ROUGE2::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	ROUGE2::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender(){
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(ROUGE2::Event& e){
	m_CameraController.OnEvent(e);
}