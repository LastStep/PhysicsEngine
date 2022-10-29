#include <Core/Window.h>
#include <Core/GLEvents.h>

Window::Window()
{
    /* Initialize the library */
    if (!glfwInit()) Window::Delete();

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
    if (!m_Window) Window::Delete();

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);
    /* Sync refresh rate to monitor's*/
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) Window::Delete();

    //glViewport(0, 0, m_Width, m_Height);
    //glMatrixMode(GL_PROJECTION);
    //glOrtho(0, m_Width, 0, m_Height, -1, 1);

    // Store contextual data, to retrive later
    GLFWUserPointerData UserPointerData{};
    UserPointerData.o_Renderer = &m_Renderer;
    glfwSetWindowUserPointer(m_Window, &UserPointerData);

    // Event callbacks
    glfwSetKeyCallback(m_Window, GLEvent::CallbackKeyboardEventOpenGL);
    glfwSetMouseButtonCallback(m_Window, GLEvent::CallbackMouseEventOpenGL);
    
    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
}

void Window::Delete()
{
    m_Renderer.Delete();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void Window::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        Window::Draw();
    }

    Window::Delete();
}

void Window::Draw()
{
    m_Renderer.Clear(m_ClearColor);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_Renderer.Draw();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    ImGui::ShowDemoWindow();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&m_ClearColor); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    /* Swap front and back buffers */
    glfwSwapBuffers(m_Window);

    /* Poll for and process events */
    glfwPollEvents();
}
