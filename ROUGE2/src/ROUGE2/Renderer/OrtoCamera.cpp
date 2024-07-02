#include "r2pch.h"
#include "OrtoCamera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace ROUGE2 {
	OrtoCamera::OrtoCamera(float left, float right, float bottom, float top)
		: m_ProjMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}
}