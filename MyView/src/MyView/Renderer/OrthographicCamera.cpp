#include "mvpch.h"
#include "OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace MyView {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f), m_Rotation(0.0f), m_Position(0.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(0, 0, 1));
		glm::mat4 ViewTranslate = glm::translate( glm::mat4(1.0f), m_Position);
		glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 ViewRotateY = glm::rotate(ViewRotateX, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 View = glm::rotate(ViewRotateY, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(View);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
