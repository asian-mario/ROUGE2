#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ROUGE2 {

    class PerspectiveCamera {
    public:
        PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip);

        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
        const glm::vec3& GetPosition() const { return m_Position; }

        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
        float GetRotation() const { return m_Rotation; }

        void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);

        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;

        float m_FOV, m_AspectRatio, m_NearClip, m_FarClip;
    };

}
