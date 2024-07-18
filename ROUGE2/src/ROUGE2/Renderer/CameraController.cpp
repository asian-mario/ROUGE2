#include "r2pch.h"
#include "CameraController.h"
#include "ROUGE2/Core/Input.h"
#include "ROUGE2/Core/KeyCodes.h"

namespace ROUGE2 {
	CameraController::CameraController(float fov, float aspectRatio, float nearClip, float farClip)
		: m_aspectRatio(aspectRatio), m_Camera(fov, aspectRatio, nearClip, farClip)
	{
	}

	void CameraController::OnUpdate(Timestep ts){
		//------------------------------------------------------
		if (Input::IsKeyPressed(R2_KEY_A)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(R2_KEY_D)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(R2_KEY_W)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(R2_KEY_S)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}


		if (Input::IsKeyPressed(R2_KEY_Q)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		if (Input::IsKeyPressed(R2_KEY_E)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		m_Camera.SetRotation(m_CameraRotation);

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void CameraController::OnEvent(Event& e){
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(R2_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(R2_BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(m_ZoomLevel, m_aspectRatio, 0.1f, 100.0f);
		return false;
	}
	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_ZoomLevel, m_aspectRatio, 0.1f, 100.0f);

		return false;
	}
}
