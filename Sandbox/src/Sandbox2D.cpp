#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach(){
	m_Texture = ROUGE2::Texture2D::Create("assets/textures/ROUGE.png");
	m_TestBGTex = ROUGE2::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach(){
}

void Sandbox2D::OnUpdate(ROUGE2::Timestep ts){
	m_CameraController.OnUpdate(ts);

	ROUGE2::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ROUGE2::RenderCommand::Clear();

	ROUGE2::Renderer2D::BeginScene(m_CameraController.GetCamera());

	ROUGE2::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.9f, 0.2f, 0.1f, 1.0f });
	ROUGE2::Renderer2D::DrawQuad({ 1.0f, -0.5f }, { 0.8f, 0.8f }, { 0.2f, 0.7f, 0.1f, 1.0f });
	ROUGE2::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.5f }, { 10.0f, 10.0f }, m_TestBGTex, false, m_TexScale);

	//------------------------------TRANSPARENT------------------------------
	//TODO: fix false blending issue if transparent object is rendered before a BG object thats behind it
	//Just render it in front for now. Too bad!
	ROUGE2::Renderer2D::DrawQuad({ 0.3f, 1.0f, 0.1f }, { 0.8f, 0.8f }, m_Texture, true, 1);


	ROUGE2::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender(){
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::SliderInt("Texture Tiling Scale", &m_TexScale, 0, 10);
	ImGui::End();
}

void Sandbox2D::OnEvent(ROUGE2::Event& e){
	m_CameraController.OnEvent(e);
}