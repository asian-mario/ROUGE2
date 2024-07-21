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

	// temp
	ROUGE2::Ref<ROUGE2::VertexArray> m_SquareVA;
	ROUGE2::Ref<ROUGE2::Shader> m_FlatColorShader;

	ROUGE2::Ref<ROUGE2::Texture2D> m_Texture, m_TestBGTex;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};