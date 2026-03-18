#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "panel.hpp"

#include <array>
#include <memory>
#include <vector>

template <typename T>
using VectorUnique = std::vector<std::unique_ptr<T>>;

class WindowUnit final {
public:
    WindowUnit(int width, int height, const std::string& title);
    ~WindowUnit();

    void SetMinWidth(int minWidth);
    void SetMinHeight(int minHeight);

    void SetColor(float r, float g, float b, float a);

    void PushPanelUnit(std::unique_ptr<PanelUnit> panelUnit);

    void Render();
    void Show();

    GLFWwindow* GetHandle() noexcept;

private:
    GLFWwindow* m_windowHandle;
    ImGuiContext* m_imguiHandle;

    int m_minWidth;
    int m_minHeight;

    std::array<float, 4> m_windowColor;

    VectorUnique<PanelUnit> m_panelUnits;
};

void WindowRefreshCallback(GLFWwindow* windowHandle);

class WindowManager final {
public:
    static std::shared_ptr<WindowManager> CreateWindowManager();

    void PushWindowUnit(std::unique_ptr<WindowUnit> windowUnit);

    void Run();

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    ~WindowManager();

private:
    WindowManager();

    static std::shared_ptr<WindowManager> m_windowManager;
    VectorUnique<WindowUnit> m_windowUnits;
};