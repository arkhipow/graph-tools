#include "window.hpp"

#include <iostream>

int main() {
    /* Manager */
    auto manager = WindowManager::Create();

    /* Window */
    auto window = UnitFactory::Create<WindowUnit>(1280, 720, "Window");

    auto button = UnitFactory::Create<ButtonUnit>(1240, 80, "Button");
    button->SetPos(20, 20);
    button->SetCallback([] { std::cout << 1 << std::endl; });

    window->Push(std::move(button));
    manager->Push(std::move(window));

    /* Run */
    manager->Run();
}