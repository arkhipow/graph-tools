#include "window.hpp"

int main() {
    auto manager = WindowManager::Create();

    auto window1 = WindowUnit::Create(1280, 720, "Window 1");
    auto window2 = WindowUnit::Create(1280, 720, "Window 2");

    manager->Push(std::move(window1));
    manager->Push(std::move(window2));

    manager->Run();
}