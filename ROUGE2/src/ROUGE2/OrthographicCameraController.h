#pragma once

#include "ROUGE2/Renderer/OrthoCamera.h"
#include "ROUGE2/Core/Timestep.h"

#include "ROUGE2/Events/ApplicationEvent.h"
#include "ROUGE2/Events/MouseEvent.h"


namespace ROUGE2 {
	class OrthographicCameraController{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthoCamera& GetCamera() { return m_Camera; }
		const OrthoCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowresized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthoCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CamPos = { 0.0f, 0.0f, 0.0f };
		float m_CamRot = 0.0f;

		float m_CamTranslationSpeed = 1.0f, m_CamRotSpeed = 60.0f;
	};
}