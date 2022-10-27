#include <iostream>

#include <Graphics/Renderer.h>
#include <Graphics/Mesh.h>

std::vector<MeshSquare*> MeshArray;


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    for (MeshSquare* mesh : MeshArray)
    {
        delete mesh;
    }
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw()
{
    for (MeshSquare* mesh : MeshArray)
    {
        mesh->Draw();
    }
}

void Renderer::HandleEvent(Event eventType, std::unordered_map<std::string, void*> eventData)
{
    switch (eventType)
    {
        case Event::KEYBOARD:
            break;
        case Event::MOUSE:
            break;
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

        MeshArray.push_back(new MeshSquare(meshSquareAttr));
    }
}
