#include <iostream>

#include <Graphics/Renderer.h>


Renderer::Renderer()
{
}

void Renderer::Delete()
{
    for (MeshSquare* mesh : m_MeshArray)
    {
        delete mesh;
    }
}

void Renderer::Clear(std::optional<ImVec4> clearColor)
{
    if (!clearColor) clearColor = m_ClearColor;
    glClearColor(clearColor->x * clearColor->w, clearColor->y * clearColor->w, clearColor->z * clearColor->w, clearColor->w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(OrthographicCameraController* cameraController)
{
    for (MeshSquare* mesh : m_MeshArray)
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
        case EventType::MOUSE:
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
    // Handling imgui input first
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(eventData.Mouse_Button, eventData.Event_Action == GLFW_PRESS);

    // Stopping event propogation from imgui to glfw
    if (io.WantCaptureMouse) return;

    if (eventData.Mouse_Button == GLFW_MOUSE_BUTTON_LEFT && eventData.Event_Action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(eventData.GLFW_Window, &xpos, &ypos);

        MeshRectangleAttributes meshSquareAttr{};
        meshSquareAttr.position   = { (float)xpos, (float)ypos, 0.0f };
        meshSquareAttr.dimensions = { 100.05f, 100.05f };

        m_MeshArray.push_back(new MeshSquare(meshSquareAttr));
    }
}
