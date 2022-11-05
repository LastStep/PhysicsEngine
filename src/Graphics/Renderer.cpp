#include <Graphics/Renderer.h>


Renderer::Renderer()
{
}

void Renderer::Delete()
{
    /*for (std::shared_ptr<Mesh> mesh : m_Meshes)
    {
        delete mesh;
    }*/
    Renderer::~Renderer();
}

void Renderer::Clear(std::optional<ImVec4> clearColor)
{
    if (!clearColor) clearColor = m_ClearColor;
    glClearColor(clearColor->x * clearColor->w, clearColor->y * clearColor->w, clearColor->z * clearColor->w, clearColor->w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(std::shared_ptr<OrthographicCameraController> cameraController)
{
    for (std::shared_ptr<Mesh> mesh : m_Meshes)
    {
        mesh->Draw(cameraController);
    }
}

void Renderer::OnEvent(EventType eventType, EventData eventData)
{
    switch (eventType)
    {
        case EventType::KEYBOARD:
            Renderer::HandleKeyboardEvent(eventData);
        case EventType::MOUSE_CLICK:
            Renderer::HandleMouseEvent(eventData);
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
        meshRectangleAttr.position   = { (float)xpos, (float)ypos, 0.0f };
        meshRectangleAttr.dimensions = { 20.0f, 20.0f };

        if (SELECTED_MESH_TYPE == MeshType::SQUARE)
            m_Meshes.push_back(std::shared_ptr<Mesh>(std::make_shared<MeshSquare>(meshRectangleAttr)));
    }
}
