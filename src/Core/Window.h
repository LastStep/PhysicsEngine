#pragma once

#include <Core/GLCore.h>
#include <Core/Event.h>
#include <Graphics/Renderer.h>
#include <Util/OrthographicCameraController.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>


class Window
{
private:
	float m_Width  = 1280.0f;
	float m_Height = 720.0f;
	const char* m_Title = "Window";
	Renderer m_Renderer;
	GLFWwindow* m_Window;
	ImVec4 m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 
	OrthographicCameraController m_CameraController;

public:
	Window();
	void Delete();

	void Run();

	void OnEvent(EventType eventType, EventData eventData);

	inline float		GetWidth()		const { return m_Width;		 }
	inline float		GetHeight()		const { return m_Height;	 }
	inline const char*  GetTitle()		const { return m_Title;		 }
	inline ImVec4		GetClearColor() const { return m_ClearColor; }
	inline Renderer* GetRenderer() { return &m_Renderer; }
	inline OrthographicCameraController* GetCameraController() { return &m_CameraController; }

protected:
	void Draw();
	void HandleWindowResizeEvent(EventData eventData);
	void HandleMouseScrollEvent(EventData eventData);
};