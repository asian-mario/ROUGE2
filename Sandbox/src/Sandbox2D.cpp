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
	OSVI_PROFILE_FUNCTION();
	
	{
		OSVI_PROFILE_SCOPE("ON ATTACH");
		m_Texture = ROUGE2::Texture2D::Create("assets/textures/ROUGE.png", true);
		m_TestBGTex = ROUGE2::Texture2D::Create("assets/textures/Checkerboard.png", false);
	}

	// Flames
	m_EngineParticle.Position = { 0.0f, 0.0f };
	m_EngineParticle.Velocity = { 0.0f, 0.0f }, m_EngineParticle.velocityVariation = { 3.0f, 1.0f };
	m_EngineParticle.sizeBegin = 0.035f, m_EngineParticle.sizeEnd = 0.0f, m_EngineParticle.sizeVariation = 0.3f;
	m_EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
	m_EngineParticle.LifeTime = 1.0f;
}

void Sandbox2D::OnDetach(){
	OSVI_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(ROUGE2::Timestep ts){

	OSVI_PROFILE_FUNCTION();


	m_CameraController.OnUpdate(ts);
	//m_ParticleSystem.OnUpdate(ts);


	{
		OSVI_PROFILE_SCOPE("PREP");
		ROUGE2::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ROUGE2::RenderCommand::Clear();

		ROUGE2::Renderer2D::BeginScene(m_CameraController.GetCamera());
	}

	{
		OSVI_PROFILE_SCOPE("RENDER DRAW");
		//For texture objects theres going to be an optional "tint" -> set to {1.0f, 1.0f, 1.0f, 1.0f} for base texture color o/  glm::vec4(1.0f)
		//ROUGE2::Renderer2D::DrawRotQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(45.0f), m_SquareColor);
		ROUGE2::Renderer2D::DrawQuad({ 1.0f, -0.5f }, { 0.8f, 0.8f }, { 0.2f, 0.7f, 0.1f, 1.0f });
		ROUGE2::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.5f }, { 10.0f, 10.0f }, m_TestBGTex, glm::vec4(1.0f), m_TileScale);

		//------------------------------TRANSPARENT------------------------------
		//TODO: fix false blending issue if transparent object is rendered before a BG object thats behind it
		//Just render it in front for now. Too bad!
		ROUGE2::Renderer2D::DrawQuad({ 0.3f, 1.0f, 0.1f }, { 0.8f, 0.8f }, m_Texture, m_TintColor);

		
		//m_ParticleSystem.Emit(m_EngineParticle);
		//m_ParticleSystem.OnRender();
		
	}


	ROUGE2::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender(){
	OSVI_PROFILE_FUNCTION();
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::SliderFloat2("FIRE Position", glm::value_ptr(m_EngineParticle.Position), -5, 5);

	ImGui::SliderFloat2("Velocity Variation", glm::value_ptr(m_EngineParticle.velocityVariation), 0, 10);
	ImGui::SliderFloat2("Velocity", glm::value_ptr(m_EngineParticle.Velocity), -10, 10);


	ImGui::SliderFloat("Texture Tiling Scale", &m_TileScale, 0, 10);
	ImGui::ColorEdit4("Tint Color", glm::value_ptr(m_TintColor));

	ImGui::End();

}

void Sandbox2D::OnEvent(ROUGE2::Event& e){
	m_CameraController.OnEvent(e);
}