#include <GLFW/glfw3.h>

int main() {
    glfwInit();

    constexpr char title[] = "graph-tools";
    GLFWwindow* window = glfwCreateWindow(1280, 720, title, nullptr, nullptr);

    while (!glfwWindowShouldClose(window)) {
        glfwWaitEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}