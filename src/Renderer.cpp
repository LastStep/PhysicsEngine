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

void Renderer::Draw()
{
    for (MeshSquare* mesh : m_MeshArray)
    {
        mesh->Draw();
    }
}

void Renderer::OnEvent(EventType eventType, EventData eventData)
{
    switch (eventType)
    {
        case EventType::KEYBOARD:
            Renderer::HandleKeyboardEventOpenGL(eventData.GLFW_window, eventData.Keyboad_Key, 0, eventData.Event_Action, 0);
        case EventType::MOUSE:
            Renderer::HandleMouseEventOpenGL(eventData.GLFW_window, eventData.Mouse_Button, eventData.Event_Action, 0);
        default:
            break;
    }
}

void Renderer::HandleKeyboardEventOpenGL(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Renderer::HandleMouseEventOpenGL(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        MeshRectangleAttributes meshSquareAttr{};
        meshSquareAttr.position = { (float)xpos, (float)ypos, 0.0f };
        meshSquareAttr.dimensions = { 100.05f, 100.05f };

        m_MeshArray.push_back(new MeshSquare(meshSquareAttr));
    }
}
