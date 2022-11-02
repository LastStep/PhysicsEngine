#include <sstream>
#include <string>

#include <Core/Window.h>
#include <Core/GLEvents.h>


Window::Window()
    : m_CameraController(m_Width, m_Height)
{
    /* Initialize the library */
    if (!glfwInit()) Window::Delete();

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title, NULL, NULL);
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
    static bool show_app_main_menu_bar = false;

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    ImGui::ShowDemoWindow();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        std::vector<MeshSquare*> meshArray = m_Renderer.GetMeshArray();

        ImGui::Begin("Mesh Counter");          
        ImGui::Text("Number of Meshes = %d", meshArray.size());
        
        std::vector<float> positionX{};
        
        for (int i = 0; i < meshArray.size(); i++)
        {
            std::string menuName = "Mesh ";
            int theInt = 5;
            std::stringstream ss;
            ss << menuName << meshArray[i]->GetID();
            ImGui::MenuItem(ss.str().c_str(), NULL, &meshArray[i]->SHOW_IN_IMGUI);
            
            if (meshArray[i]->SHOW_IN_IMGUI)
            {
                ImGui::PushID(i);
                ImGui::ColorEdit4("Mesh Color", (float*)meshArray[i]->GetColor());
                ImGui::SliderFloat("Mesh Position X", &meshArray[i]->GetOffset()->x, -1.0f * m_Width / 2, m_Width / 2);
                ImGui::SliderFloat("Mesh Position Y", &meshArray[i]->GetOffset()->y, -1.0f * m_Height / 2, m_Height / 2);
                ImGui::PopID();
            }
        }

        ImGui::End();
    }

    {
        ImGui::Begin("Renderer");
        ImGui::Checkbox("Enable Click to Draw", &m_Renderer.ENABLE_CLICK);
        ImGui::BeginGroup();
        if (ImGui::Button("None"))
            m_Renderer.SELECTED_MESH_TYPE = MeshType::NONE;
        if (ImGui::Button("Square"))
            m_Renderer.SELECTED_MESH_TYPE = MeshType::SQUARE;
        ImGui::EndGroup();
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
    glViewport(0, 0, (GLsizei)m_Width, (GLsizei)m_Height);
}

void Window::HandleMouseScrollEvent(EventData eventData)
{
    //float zoomLevel = m_CameraController.GetZoomLevel();
    //glViewport(0, 0, m_Width * zoomLevel, m_Height * zoomLevel);
}