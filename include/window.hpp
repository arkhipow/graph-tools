#pragma once
#include <glfw/glfw3.h>
#include <memory>
#include <string>
#include <vector>

class WindowUnit final {
public:
    WindowUnit(int width, int height, const std::string& title);
    ~WindowUnit();

    void Render();
    void Show();

    GLFWwindow* GetHandle() noexcept;

private:
    GLFWwindow* m_windowHandle;
};

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