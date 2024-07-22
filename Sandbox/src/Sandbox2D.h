#pragma once

#include "ROUGE2.h"

class Sandbox2D : public ROUGE2::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(ROUGE2::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ROUGE2::Event& e) override;
private:
	ROUGE2::OrthographicCameraController m_CameraController;


	ROUGE2::Ref<ROUGE2::Texture2D> m_Texture, m_TestBGTex;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 m_TintColor = { 1.0f, 1.0, 1.0, 1.0f };
	int m_TexScale = 1;

	struct ProfileResult {
		const char* Name;
		float time;
	};

	std::vector<ProfileResult> m_ProfileResults;
};