#pragma once

#include "MyView/Renderer/OrthographicCamera.h"
#include "MyView/Core/Timestep.h"

#include "MyView/Events/ApplicationEvent.h"
#include "MyView/Events/MouseEvent.h"


namespace MyView {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio = 0.0f;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraRotation = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 2.0f;
		float m_CameraRotationSpeed = 2.0f;
		float m_PrevMousePosX;
		float m_PrevMousePosY;
	};
}
