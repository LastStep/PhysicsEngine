#pragma once

#include <vector>
#include <unordered_map>
#include <optional>
#include <memory>

#include <Core/GLCore.h>
#include <Core/Event.h>
#include <Graphics/Mesh.h>
#include <Util/OrthographicCameraController.h>
#include <Physics/Core.h>
#include <imgui.h>


enum class MeshType
{
    NONE,
    SQUARE
};


class Renderer
{
private:
    std::shared_ptr<Physics::PhysicsWorld> m_PhysicsWorld;
    std::vector<std::shared_ptr<Physics::PhysicsObject>> m_PhysicsObjects;
    std::vector<std::shared_ptr<Mesh>> m_Meshes;
    ImVec4 m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

public:
    Renderer();
    void Delete();
    void Clear(std::optional<ImVec4> clearColor = std::nullopt);
    void Draw(float ts, std::shared_ptr<OrthographicCameraController> cameraController);
    void OnEvent(EventType eventType, EventData eventData);

    inline std::vector<std::shared_ptr<Mesh>> GetMeshes() { return m_Meshes; }

    bool ENABLE_CLICK = true;
    MeshType SELECTED_MESH_TYPE = MeshType::NONE;

protected:
    void HandleKeyboardEvent(EventData eventData);
    void HandleMouseEvent(EventData eventData);

};