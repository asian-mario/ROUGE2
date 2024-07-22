#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

template<typename Fn> 
class Timer {
public:
	Timer(const char* name, Fn&& func) 
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		if (!m_Stopped)
			Stop();
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;

		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};


#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

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

	PROFILE_SCOPE("SANDBOX2D UPDATE");

	m_CameraController.OnUpdate(ts);

	ROUGE2::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ROUGE2::RenderCommand::Clear();

	ROUGE2::Renderer2D::BeginScene(m_CameraController.GetCamera());

	{
		PROFILE_SCOPE("RENDER DRAW");
		//For texture objects theres going to be an optional "tint" -> set to {1.0f, 1.0f, 1.0f, 1.0f} for base texture color o/  glm::vec4(1.0f)
		ROUGE2::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
		ROUGE2::Renderer2D::DrawQuad({ 1.0f, -0.5f }, { 0.8f, 0.8f }, { 0.2f, 0.7f, 0.1f, 1.0f });
		ROUGE2::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.5f }, { 10.0f, 10.0f }, m_TestBGTex, false, m_TexScale, glm::vec4(1.0f));

		//------------------------------TRANSPARENT------------------------------
		//TODO: fix false blending issue if transparent object is rendered before a BG object thats behind it
		//Just render it in front for now. Too bad!
		ROUGE2::Renderer2D::DrawQuad({ 0.3f, 1.0f, 0.1f }, { 0.8f, 0.8f }, m_Texture, true, 1, m_TintColor);
	}


	ROUGE2::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender(){
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::SliderInt("Texture Tiling Scale", &m_TexScale, 0, 10);
	ImGui::ColorEdit4("Tint Color", glm::value_ptr(m_TintColor));

	ImGui::End();

	ImGui::Begin("Diagnostics");
	for (auto& results : m_ProfileResults) {
		char label[50];
		strcpy(label, "%.3fms: ");
		strcat(label, results.Name);

		ImGui::Text(label, results.time);
	}

	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(ROUGE2::Event& e){
	m_CameraController.OnEvent(e);
}