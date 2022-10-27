#pragma once

#include <vector>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


enum class Event
{
    KEYBOARD,
    MOUSE
};


class Renderer
{
private:

public:
    Renderer();
    ~Renderer();
    void Clear();
    void Draw();
    void HandleEvent(Event eventType, std::unordered_map<std::string, void*> eventData);

    static void HandleKeyboardEventOpenGL(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void HandleMouseEventOpenGL(GLFWwindow* window, int button, int action, int mods);

};