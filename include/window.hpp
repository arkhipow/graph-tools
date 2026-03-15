#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <array>
#include <memory>
#include <string>
#include <vector>

class WindowUnit final {
public:
    WindowUnit(int width, int height, const std::string& title);
    ~WindowUnit();

    void SetMinWidth(int minWidth);
    void SetMinHeight(int minHeight);

    void SetColor(float r, float g, float b, float a);

    void Render();
    void Show();

    GLFWwindow* GetHandle() noexcept;

private:
    GLFWwindow* m_windowHandle;
    ImGuiContext* m_imguiHandle;

    int m_minWidth;
    int m_minHeight;

    std::array<float, 4> m_windowColor;
};

void WindowRefreshCallback(GLFWwindow* windowHandle);

class WindowManager final {
public:
    static std::shared_ptr<WindowManager> CreateWindowManager();

    void Push(std::unique_ptr<WindowUnit> windowUnit);

    void Run();

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    ~WindowManager();

private:
    WindowManager();

    template <typename T>
    using VectorUnique = std::vector<std::unique_ptr<T>>;

    static std::shared_ptr<WindowManager> m_windowManager;
    VectorUnique<WindowUnit> m_windowUnits;
};