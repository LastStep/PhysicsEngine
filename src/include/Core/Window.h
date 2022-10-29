#pragma once

#include <string>
#include <Core/GLCore.h>
#include <Graphics/Renderer.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>


struct GLFWUserPointerData {
	Renderer* o_Renderer;
};


class Window
{
private:
	uint32_t m_Width  = 1280;
	uint32_t m_Height = 720;
	const char* m_Title = "Window";
	Renderer m_Renderer;
	GLFWwindow* m_Window;
	ImVec4 m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 

public:
	Window();
	void Delete();

	void Run();

	inline uint32_t		GetWidth()		const { return m_Width;		 }
	inline uint32_t		GetHeight()		const { return m_Height;	 }
	inline const char*  GetTitle()		const { return m_Title;		 }
	inline ImVec4		GetClearColor() const { return m_ClearColor; }


protected:
	void Draw();

};