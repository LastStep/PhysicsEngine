#pragma once

#include <vector>
#include <unordered_map>
#include <optional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <Core/Event.h>
#include <Graphics/Mesh.h>


class Renderer
{
private:
    std::vector<MeshSquare*> m_MeshArray;
	ImVec4 m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 

public:
    Renderer();
    void Delete();
    void Clear(std::optional<ImVec4> clearColor = std::nullopt);
    void Draw();
    void OnEvent(EventType eventType, EventData eventData);

protected:
    void HandleKeyboardEventOpenGL(GLFWwindow* window, int key, int scancode, int action, int mods);
    void HandleMouseEventOpenGL(GLFWwindow* window, int button, int action, int mods);

};