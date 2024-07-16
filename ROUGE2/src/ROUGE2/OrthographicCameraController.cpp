#include "r2pch.h"
#include "OrthographicCameraController.h"

#include "ROUGE2/Input.h"
#include "ROUGE2/KeyCodes.h"
namespace ROUGE2 {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}


	void OrthographicCameraController::OnUpdate(Timestep ts){
		//------------------------------------------------------
		if (Input::IsKeyPressed(R2_KEY_A)) {
			m_CamPos.x -= m_CamTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(R2_KEY_D)) {
			m_CamPos.x += m_CamTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(R2_KEY_W)) {
			m_CamPos.y += m_CamTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(R2_KEY_S)) {
			m_CamPos.y -= m_CamTranslationSpeed * ts;
		}

		//------------------------------------------------------
		if (m_Rotation) {
			if (Input::IsKeyPressed(R2_KEY_Q)) {
				m_CamRot -= m_CamRotSpeed * ts;
			}
			if (Input::IsKeyPressed(R2_KEY_E)) {
				m_CamRot += m_CamRotSpeed * ts;
			}
			m_Camera.SetRotation(m_CamRot);
		}
		//------------------------------------------------------

		m_Camera.SetPosition(m_CamPos);
		m_CamTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e){
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(R2_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(R2_BIND_EVENT_FN(OrthographicCameraController::OnWindowresized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e){
		m_ZoomLevel -= (e.GetYOffset()) / 2;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProj(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowresized(WindowResizeEvent& e){
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetWidth();
		m_Camera.SetProj(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}