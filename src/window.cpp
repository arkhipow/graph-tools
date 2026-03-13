#include "window.hpp"

WindowUnit::WindowUnit(int width, int height, const std::string& title) : m_windowHandle(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)) {
    if (!m_windowHandle) {}
}

WindowUnit::~WindowUnit() {
    glfwDestroyWindow(m_windowHandle);
}

void WindowUnit::Render() {
    glfwMakeContextCurrent(m_windowHandle);

    /* Rendering */

    glfwSwapBuffers(m_windowHandle);
}

void WindowUnit::Show() {
    glfwShowWindow(m_windowHandle);
}

GLFWwindow* WindowUnit::GetHandle() noexcept {
    return m_windowHandle;
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