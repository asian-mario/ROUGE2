#pragma once

#include "PerspectiveCamera.h"
#include "ROUGE2/Core/Timestep.h"
#include "ROUGE2/Events/ApplicationEvent.h"
#include "ROUGE2/Events/MouseEvent.h"

namespace ROUGE2 {

	class CameraController {
	public:
		CameraController(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_aspectRatio;
		float m_ZoomLevel = 1.0f;
		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}