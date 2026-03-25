#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "panel.hpp"

template <typename T>
using VectorUnique = std::vector<std::unique_ptr<T>>;

class WindowUnit final : ObjectUnit {
public:
    WindowUnit(int width, int height, const std::string& title);
    ~WindowUnit();

    void Push(std::unique_ptr<PanelUnit> unit);
    void Render();

    GLFWwindow* GetHandle() const noexcept { return m_handle; }
    ImGuiContext* GetContext() const noexcept { return m_context; }

    WindowUnit(const WindowUnit&) = delete;
    WindowUnit& operator=(const WindowUnit&) = delete;

private:
    void NewFrame();
    void EndFrame();

    void SetScale();

    GLFWwindow* m_handle;
    ImGuiContext* m_context;

    VectorUnique<PanelUnit> m_units;
};

class WindowManager final {
public:
    [[nodiscard]] static std::unique_ptr<WindowManager> Create();
    ~WindowManager();

    void Push(std::unique_ptr<WindowUnit> unit);
    void Run();

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

private:
    WindowManager();

    static void UpdateContext(WindowUnit* unit);

    static bool m_isCreated;
    VectorUnique<WindowUnit> m_units;
};