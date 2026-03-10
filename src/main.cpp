#include "window.hpp"
#include <stdexcept>

int main() {
    if (!glfwInit()) {
        throw (std::runtime_error("Failed to initialize GLFW"));
    }

    std::string title = "GraphTools";
    GraphTools::Window myWindow(1280, 720, title);

    myWindow.Run();

    glfwTerminate();
    return 0;
}