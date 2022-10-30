#include <Util/OrthographicCameraController.h>


OrthographicCameraController::OrthographicCameraController(float width, float height, bool rotation)
	:	m_Width(width),
		m_Height(height),
		m_AspectRatio(m_Width / m_Height),
		m_Camera(0.0f, m_Width * m_ZoomLevel, m_Height * m_ZoomLevel, 0.0f),
		m_Rotation(rotation)
{
}

void OrthographicCameraController::OnUpdate(float ts)
{
	/*if (Input::IsKeyPressed(HZ_KEY_A))
	{
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(HZ_KEY_D))
	{
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}

	if (Input::IsKeyPressed(HZ_KEY_W))
	{
		m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(HZ_KEY_S))
	{
		m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}

	if (m_Rotation)
	{
		if (Input::IsKeyPressed(HZ_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Input::IsKeyPressed(HZ_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_Camera.SetRotation(m_CameraRotation);
	}

	m_Camera.SetPosition(m_CameraPosition);

	m_CameraTranslationSpeed = m_ZoomLevel;*/
}

void OrthographicCameraController::OnEvent(EventType eventType, EventData eventData)
{
	switch (eventType)
	{
		case EventType::WINDOW:
			OrthographicCameraController::HandleWindowEvent(eventData);
		case EventType::KEYBOARD:
			OrthographicCameraController::HandleKeyboardEvent(eventData);
		case EventType::MOUSE:
			OrthographicCameraController::HandleMouseEvent(eventData);
		default:
			break;
	}
}

void OrthographicCameraController::HandleWindowEvent(EventData eventData)
{
	m_Width = eventData.Window_Width;
	m_Height = eventData.Window_Height;
	m_AspectRatio = m_Width / m_Height;
	m_Camera.SetProjection(0.0f, m_Width * m_ZoomLevel, m_Height * m_ZoomLevel, 0.0f);
}

void OrthographicCameraController::HandleKeyboardEvent(EventData eventData)
{
}

void OrthographicCameraController::HandleMouseEvent(EventData eventData)
{
	/*m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);*/
}