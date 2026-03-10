#include "window.hpp"
#include <stdexcept>

GraphTools::Window::Window(int width, int height, const std::string& title) {
    m_hWnd = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_hWnd) { throw (std::runtime_error("Failed to create GLFW window")); }

    glfwMakeContextCurrent(m_hWnd);
    glfwSetFramebufferSizeCallback(m_hWnd, ResizeCallback);

    glClearColor(windowColor.m_r, windowColor.m_g, windowColor.m_b, windowColor.m_a);
}

GraphTools::Window::~Window() {
    glfwDestroyWindow(m_hWnd);
}

void GraphTools::Window::ClearFrame(HWINDOW hWnd) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(hWnd);
}

void GraphTools::Window::Run() {
    while (!glfwWindowShouldClose(m_hWnd)) {
        glfwPollEvents();
        ClearFrame(m_hWnd);
    }
}

void GraphTools::Window::ResizeCallback(HWINDOW hWnd, int width, int height) {
    glViewport(0, 0, width, height);
    ClearFrame(hWnd);
}