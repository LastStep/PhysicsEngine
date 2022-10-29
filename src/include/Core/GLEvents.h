#pragma once

#include <Core/GLCore.h>
#include <Core/Event.h>
#include <Core/Window.h>


namespace GLEvent {
    void CallbackKeyboardEventOpenGL(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        EventData eventData{};
        eventData.GLFW_window = window;
        eventData.Keyboad_Key = key;
        eventData.Event_Action = action;

        GLFWUserPointerData* UserPointerData = (GLFWUserPointerData*)glfwGetWindowUserPointer(window);
        UserPointerData->o_Renderer->OnEvent(EventType::KEYBOARD, eventData);
    }

    void CallbackMouseEventOpenGL(GLFWwindow* window, int button, int action, int mods)
    {
        // Handling imgui input first
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(button, action == GLFW_PRESS);

        // Stopping event propogation from imgui to glfw
        if (!io.WantCaptureMouse)
        {
            EventData eventData{};
            eventData.GLFW_window = window;
            eventData.Mouse_Button = button;
            eventData.Event_Action = action;

            GLFWUserPointerData* UserPointerData = (GLFWUserPointerData*)glfwGetWindowUserPointer(window);
            UserPointerData->o_Renderer->OnEvent(EventType::MOUSE, eventData);
        }
    }
}