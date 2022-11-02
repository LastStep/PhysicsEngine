#pragma once

#include <Core/GLCore.h>
#include <Core/Event.h>
#include <Core/Window.h>
#include <iostream>

namespace GLEvent {
    // Window Events
    void CallbackOpenGLWindowResizeEvent(GLFWwindow* GLFW_window, int width, int height)
    {
        EventData eventData{};
        eventData.GLFW_Window = GLFW_window;
        eventData.Window_Width = (float)width;
        eventData.Window_Height = (float)height;

        Window* W_window = (Window*)glfwGetWindowUserPointer(GLFW_window);
        W_window->OnEvent(EventType::WINDOW_RESIZE, eventData);
        W_window->GetCameraController()->OnEvent(EventType::WINDOW_RESIZE, eventData);
    }

    // Keyboard Events
    void CallbackOpenGLKeyboardEvent(GLFWwindow* GLFW_window, int key, int scancode, int action, int mods)
    {
        EventData eventData{};
        eventData.GLFW_Window = GLFW_window;
        eventData.Keyboad_Key = key;
        eventData.Event_Action = action;

        Window* W_window = (Window*)glfwGetWindowUserPointer(GLFW_window);
        W_window->GetRenderer()->OnEvent(EventType::KEYBOARD, eventData);
    }

    // Mouse Events
    void CallbackOpenGLMouseClickEvent(GLFWwindow* GLFW_window, int button, int action, int mods)
    {
        // Handling imgui input first
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(button, action == GLFW_PRESS);

        // Stopping event propogation from imgui
        if (io.WantCaptureMouse) return;

        EventData eventData{};
        eventData.GLFW_Window = GLFW_window;
        eventData.Mouse_Button = button;
        eventData.Event_Action = action;

        Window* W_window = (Window*)glfwGetWindowUserPointer(GLFW_window);
        W_window->GetRenderer()->OnEvent(EventType::MOUSE_CLICK, eventData);
    }

    void CallbackOpenGLMouseScrollEvent(GLFWwindow* GLFW_window, double xoffset, double yoffset)
    {
        EventData eventData{};
        eventData.GLFW_Window = GLFW_window;
        eventData.Scroll_XOffset = xoffset;
        eventData.Scroll_YOffset = yoffset;

        Window* W_window = (Window*)glfwGetWindowUserPointer(GLFW_window);
        W_window->GetCameraController()->OnEvent(EventType::MOUSE_SCROLL, eventData);
        W_window->OnEvent(EventType::MOUSE_SCROLL, eventData);
    }

}