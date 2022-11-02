#pragma once

#include <Core/Event.h>
#include <Util/OrthographicCamera.h>


class OrthographicCameraController
{
private:
	float m_Width;
	float m_Height;
	float m_AspectRatio;
	float m_ZoomLevel = 1.0f;
	float m_ZoomMagnitude = 0.25f;
	OrthographicCamera m_Camera;

	bool m_Rotation;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
	float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

public:
	OrthographicCameraController(float width, float height, bool rotation = false);

	void OnUpdate(float ts);
	void OnEvent(EventType eventType, EventData eventData);

	inline OrthographicCamera& GetCamera() { return m_Camera; }
	inline const OrthographicCamera& GetCamera() const { return m_Camera; }

	inline float GetZoomLevel() const { return m_ZoomLevel; }

protected:
	void HandleWindowResizeEvent(EventData eventData);
	void HandleMouseScrollEvent(EventData eventData);
};