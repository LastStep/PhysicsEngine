#include <Graphics/Renderer.h>


Renderer::Renderer()
    : m_PhysicsWorld(std::make_shared<Physics::PhysicsWorld>())
{
}

void Renderer::Delete()
{
    Renderer::~Renderer();
}

void Renderer::Clear(std::optional<ImVec4> clearColor)
{
    if (!clearColor) clearColor = m_ClearColor;
    glClearColor(clearColor->x * clearColor->w, clearColor->y * clearColor->w, clearColor->z * clearColor->w, clearColor->w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(float ts, OrthographicCameraController* cameraController)
{
    m_PhysicsWorld->Step(ts);
    for (int i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes[i]->m_MeshTransform.Position = m_PhysicsObjects[i]->GetPosition();
        m_Meshes[i]->Draw(cameraController);
    }
}

void Renderer::AddObject(MeshType meshType, void* meshAttr)
{
    switch (meshType)
    {
        case MeshType::NONE:
            break;
        case MeshType::SQUARE:
        {
            MeshRectangleAttributes* meshRectangleAttr = (MeshRectangleAttributes*)meshAttr;
            m_Meshes.push_back(std::shared_ptr<Mesh>(std::make_shared<MeshSquare>(*meshRectangleAttr)));
            
            std::shared_ptr<Physics::PhysicsObject> physicsObject = std::make_shared<Physics::PhysicsObject>(meshRectangleAttr->Position);
            physicsObject->IS_STATIC = SELECTED_STATIC;
            
            m_PhysicsObjects.push_back(physicsObject);
            m_PhysicsWorld->AddObject(physicsObject.get());
        }
            break;
        default:
            break;
    }
}

void Renderer::RemoveObject(unsigned int objectID)
{
    for (int i = 0; i < m_Meshes.size(); i++)
    {
        if (m_Meshes[i]->GetID() == objectID)
        {
            m_Meshes.erase(std::remove(m_Meshes.begin(), m_Meshes.end(), m_Meshes[i]), m_Meshes.end());
            m_PhysicsObjects.erase(std::remove(m_PhysicsObjects.begin(), m_PhysicsObjects.end(), m_PhysicsObjects[i]), m_PhysicsObjects.end());
            m_PhysicsWorld->RemoveObject(m_PhysicsObjects[i].get());
        }
    }
}


void Renderer::OnEvent(EventType eventType, EventData eventData)
{
    switch (eventType)
    {
        case EventType::KEYBOARD:
            Renderer::HandleKeyboardEvent(eventData);
            break;
        case EventType::MOUSE_CLICK:
            Renderer::HandleMouseEvent(eventData);
            break;
        default:
            break;
    }
}

void Renderer::HandleKeyboardEvent(EventData eventData)
{
    if (eventData.Keyboad_Key == GLFW_KEY_SPACE && eventData.Event_Action == GLFW_PRESS)
        glfwSetWindowShouldClose(eventData.GLFW_Window, GLFW_TRUE);
}

void Renderer::HandleMouseEvent(EventData eventData)
{
    if (!ENABLE_CLICK) return;

    if (eventData.Mouse_Button == GLFW_MOUSE_BUTTON_LEFT && eventData.Event_Action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(eventData.GLFW_Window, &xpos, &ypos);

        MeshRectangleAttributes meshRectangleAttr{};
        meshRectangleAttr.Position   = { (float)xpos, (float)ypos, 0.0f };
        meshRectangleAttr.Dimensions = { 20.0f, 20.0f };

        Renderer::AddObject(SELECTED_MESH_TYPE, &meshRectangleAttr);
    }
}
