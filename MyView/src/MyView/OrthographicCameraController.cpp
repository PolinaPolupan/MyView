#include "mvpch.h"
#include "OrthographicCameraController.h"

#include "MyView/Input.h"
#include "MyView/KeyCodes.h"
#include "MyView/MouseButtonCodes.h"

namespace MyView {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		: m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_AspectRatio(aspectRatio)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		/*----------------- Camera Testing -------------------------------------------------*/
		bool shift = Input::IsKeyPressed(MV_KEY_RIGHT_SHIFT) || Input::IsKeyPressed(MV_KEY_LEFT_SHIFT);
		bool middleMouseButton = Input::IsMouseButtonPressed(MV_MOUSE_BUTTON_MIDDLE);

		if (shift && middleMouseButton)
		{
			auto pos = m_Camera.GetPosition();
			auto mousePos = Input::GetMousePos();

			auto mousePosX = m_PrevMousePosX - mousePos.first;
			auto mousePosY = m_PrevMousePosY - mousePos.second;
			m_PrevMousePosX = mousePos.first;
			m_PrevMousePosY = mousePos.second;
			float len = std::sqrt((mousePosX * mousePosX + mousePosY * mousePosY));
			if (len > 0.1f)
			{
				m_CameraPosition = { m_CameraPosition.x + (mousePosX / len) * m_CameraTranslationSpeed * ts, m_CameraPosition.y - (mousePosY / len) * m_CameraTranslationSpeed * ts, m_CameraPosition.z };
			}
		}
		m_CameraTranslationSpeed = m_ZoomLevel;
		m_Camera.SetPosition(m_CameraPosition);
		/*------------------------------------------------------------------*/
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(MV_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(MV_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.1f);
		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}

