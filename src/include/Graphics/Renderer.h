#pragma once

#include <vector>
#include <unordered_map>
#include <optional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <Core/Event.h>
#include <Graphics/Mesh.h>
#include <Util/OrthographicCameraController.h>


class Renderer
{
private:
    std::vector<MeshSquare*> m_MeshArray;
	ImVec4 m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

public:
    Renderer();
    void Delete();
    void Clear(std::optional<ImVec4> clearColor = std::nullopt);
    void Draw(OrthographicCameraController* cameraController);
    void OnEvent(EventType eventType, EventData eventData);

    inline std::vector<MeshSquare*> GetMeshArray() { return m_MeshArray; }
protected:
    void HandleKeyboardEvent(EventData eventData);
    void HandleMouseEvent(EventData eventData);

};