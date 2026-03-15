#include "window.hpp"

WindowUnit::WindowUnit(int width, int height, const std::string& title) : m_minWidth(GLFW_DONT_CARE), m_minHeight(GLFW_DONT_CARE) {
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    m_windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_windowHandle) {}

    glfwMakeContextCurrent(m_windowHandle);
    // glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {}

    IMGUI_CHECKVERSION();
    m_imguiHandle = ImGui::CreateContext();
    ImGui::SetCurrentContext(m_imguiHandle);

    ImGuiIO& io = ImGui::GetIO();

    float scaleX, scaleY;
    glfwGetWindowContentScale(m_windowHandle, &scaleX, &scaleY);

    ImGui::GetStyle().ScaleAllSizes(scaleX);

    ImFontConfig fontConfig;
    fontConfig.SizePixels = 14.0f * scaleX;
    io.Fonts->AddFontDefault(&fontConfig);

    ImGui_ImplGlfw_InitForOpenGL(m_windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    glfwSetWindowUserPointer(m_windowHandle, this);
    glfwSetWindowRefreshCallback(m_windowHandle, WindowRefreshCallback);
}

WindowUnit::~WindowUnit() {
    ImGui::SetCurrentContext(m_imguiHandle);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(m_imguiHandle);

    glfwDestroyWindow(m_windowHandle);
}

void WindowUnit::SetMinWidth(int minWidth) {
    m_minWidth = minWidth;
    glfwSetWindowSizeLimits(m_windowHandle, minWidth, m_minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void WindowUnit::SetMinHeight(int minHeight) {
    m_minHeight = minHeight;
    glfwSetWindowSizeLimits(m_windowHandle, m_minWidth, minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

void WindowUnit::SetColor(float r, float g, float b, float a) {
    m_windowColor = { r, g, b, a };
}

void WindowUnit::Render() {
    glfwMakeContextCurrent(m_windowHandle);
    ImGui::SetCurrentContext(m_imguiHandle);

    int width, height;
    glfwGetFramebufferSize(m_windowHandle, &width, &height);

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    ImGui::Text("Window ID: %p", m_windowHandle);
    ImGui::End();

    glViewport(0, 0, width, height);
    glClearColor(m_windowColor[0], m_windowColor[1], m_windowColor[2], m_windowColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_windowHandle);
}

void WindowUnit::Show() {
    glfwShowWindow(m_windowHandle);
}

GLFWwindow* WindowUnit::GetHandle() noexcept {
    return m_windowHandle;
}

void WindowRefreshCallback(GLFWwindow* windowHandle) {
    WindowUnit* windowUnit = static_cast<WindowUnit*>(glfwGetWindowUserPointer(windowHandle));
    windowUnit->Render();
}

std::shared_ptr<WindowManager> WindowManager::m_windowManager = nullptr;

std::shared_ptr<WindowManager> WindowManager::CreateWindowManager() {
    if (!m_windowManager) { m_windowManager = std::shared_ptr<WindowManager>(new WindowManager); }
    return m_windowManager;
}

void WindowManager::Push(std::unique_ptr<WindowUnit> windowUnit) {
    windowUnit->Show();

    m_windowUnits.push_back(std::move(windowUnit));
}

void WindowManager::Run() {
    while (!m_windowUnits.empty()) {
        glfwPollEvents();

        for (auto pWindowUnit = m_windowUnits.begin(); pWindowUnit != m_windowUnits.end(); ) {
            GLFWwindow* windowHandle = (*pWindowUnit)->GetHandle();

            if (glfwWindowShouldClose(windowHandle)) {
                pWindowUnit = m_windowUnits.erase(pWindowUnit);
                continue;
            }

            (*pWindowUnit)->Render();
            ++pWindowUnit;
        }
    }
}

WindowManager::WindowManager() {
    if (!glfwInit()) {}
}

WindowManager::~WindowManager() {
    glfwTerminate();
}