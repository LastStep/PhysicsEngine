#include <iostream>
#include <array>
#include <functional>

#include <Graphics/GLCore.h>
#include <Graphics/Renderer.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>


int initializeGLFW(int windowHeight, int windowWidth);

int main(void)
{
    initializeGLFW(1280, 720);
    return 0;
}

int initializeGLFW(int windowWidth, int windowHeight)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Sync refresh rate to monitor's*/
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW init Error" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    Renderer renderer;

    //auto handleMouseEventOpenGL = [&](GLFWwindow* window, int button, int action, int mods)
    //{
     //   renderer.HandleMouseEventOpenGL(window, button, action, mods);
    //};

    /*std::function<int> handleMouseEventOpenGL = [](GLFWwindow* window, int button, int action, int mods)
    {
        renderer.HandleMouseEventOpenGL(window, button, action, mods);
        return 0;
    };*/

    glfwSetKeyCallback(window, Renderer::HandleKeyboardEventOpenGL);
    glfwSetMouseButtonCallback(window, Renderer::HandleMouseEventOpenGL);

    bool show_demo_window = true;
    bool show_another_window = false;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    {
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            renderer.Draw();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    renderer.~Renderer();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

