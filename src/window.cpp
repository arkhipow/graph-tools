#include "window.hpp"

WindowUnit::WindowUnit(int width, int height, const std::string& title) {

}

std::shared_ptr<WindowManager> WindowManager::m_windowManager = nullptr;

std::shared_ptr<WindowManager> WindowManager::CreateWindowManager() {
    if (!m_windowManager) { m_windowManager = std::shared_ptr<WindowManager>(new WindowManager); }
    return m_windowManager;
}

void WindowManager::Push(std::unique_ptr<WindowUnit> windowUnit) {
    m_windowUnits.push_back(std::move(windowUnit));
}

void WindowManager::Run() {
    while (!m_windowUnits.empty()) {
        for (auto& windowUnit : m_windowUnits) {
            glfwPollEvents();
        }
    }
}

WindowManager::WindowManager() {
    if (!glfwInit()) {}
}

WindowManager::~WindowManager() {
    glfwTerminate();
}