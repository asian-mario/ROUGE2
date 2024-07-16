#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ROUGE2 {
	class OrthoCamera {
	public:
		OrthoCamera(float left, float right, float bottom, float top);
		void SetProj(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3 position) {
			m_Position = position; RecalculateViewMatrix();
		}

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) {
			m_Rotation = rotation; RecalculateViewMatrix();
		}

		const glm::mat4& GetProjMatrix() const { return m_ProjMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjMatrix() const { return m_ViewProjMatrix; }

	private:
		void RecalculateViewMatrix() {
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
			m_ViewMatrix = glm::inverse(transform);
			m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
		};

	private:
		glm::mat4 m_ProjMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjMatrix;


		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}