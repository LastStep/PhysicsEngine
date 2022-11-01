#include <Core/Window.h>
#include <Core/GLEvents.h>

Window::Window()
    : m_CameraController(m_Width, m_Height)
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

    /*float zoomLevel = m_CameraController.GetZoomLevel();
    glViewport(
        -1.0f * m_Width / 2.0f * zoomLevel, 
        -1.0f * m_Height / 2.0f * zoomLevel, 
        +1.0f * m_Width / 2.0f * zoomLevel,
        +1.0f * m_Height / 2.0f * zoomLevel
    )*/;

    glfwSetWindowUserPointer(m_Window, this);

    // Event callbacks
    glfwSetWindowSizeCallback(m_Window, GLEvent::CallbackOpenGLWindowResizeEvent);
    glfwSetKeyCallback(m_Window, GLEvent::CallbackOpenGLKeyboardEvent);
    glfwSetMouseButtonCallback(m_Window, GLEvent::CallbackOpenGLMouseClickEvent);
    glfwSetScrollCallback(m_Window, GLEvent::CallbackOpenGLMouseScrollEvent);

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

void Window::OnEvent(EventType eventType, EventData eventData)
{
    switch (eventType)
    {
        case EventType::WINDOW_RESIZE:
            Window::HandleWindowResizeEvent(eventData);
        case EventType::MOUSE_SCROLL:
            Window::HandleMouseScrollEvent(eventData);
        default:
            break;
    }
}

void Window::Draw()
{
    m_Renderer.Clear(m_ClearColor);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_Renderer.Draw(&m_CameraController);

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    ImGui::ShowDemoWindow();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        std::vector<MeshSquare*> meshArray = m_Renderer.GetMeshArray();

        ImGui::Begin("Mesh Counter");          
        ImGui::Text("Number of Meshes = %d", meshArray.size());
            //glm::vec4 meshColor = ;
        
        for (int i = 0; i < meshArray.size(); i++)
        {
            ImGui::PushID(i);
            ImGui::ColorEdit4("clear color", (float*)meshArray[i]->GetColor());
            ImGui::PopID();
        }

        //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    /* Swap front and back buffers */
    glfwSwapBuffers(m_Window);

    /* Poll for and process events */
    glfwPollEvents();
}

void Window::HandleWindowResizeEvent(EventData eventData)
{
    m_Width = eventData.Window_Width;
    m_Height = eventData.Window_Height;
    glViewport(0, 0, m_Width, m_Height);
}

void Window::HandleMouseScrollEvent(EventData eventData)
{
    //float zoomLevel = m_CameraController.GetZoomLevel();
    //glViewport(0, 0, m_Width * zoomLevel, m_Height * zoomLevel);
}
