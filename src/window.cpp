#include "window.hpp"

WindowUnit::WindowUnit(int width, int height, const std::string& title)
: m_windowHandle(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)), m_minWidth(GLFW_DONT_CARE), m_minHeight(GLFW_DONT_CARE) {
    if (!m_windowHandle) {}

    glfwMakeContextCurrent(m_windowHandle);

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(m_windowHandle, this);
    glfwSetWindowRefreshCallback(m_windowHandle, WindowRefreshCallback);
}

WindowUnit::~WindowUnit() {
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
    if (glfwGetCurrentContext() != m_windowHandle) {
        glfwMakeContextCurrent(m_windowHandle);
    }

    int width, height;
    glfwGetFramebufferSize(m_windowHandle, &width, &height);

    glViewport(0, 0, width, height);

    /* Rendering */
    glClearColor(m_windowColor[0], m_windowColor[1], m_windowColor[2], m_windowColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);

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