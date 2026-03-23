#include "window.hpp"

#include <iostream>

int main() {
    /* Manager */
    auto manager = WindowManager::Create();

    /* Window 1 */
    auto window1 = WindowUnit::Create(1280, 720, "Window 1");

    auto button1 = ButtonUnit::Create(20, 20, 1240, 80, "Button 1");
    button1->SetCallback([] { std::cout << 1 << std::endl; });
    window1->Push(std::move(button1));

    std::vector<float> values1;
    for (float i = -10; i <= 10; i += 0.1) {
        values1.push_back(std::sin(2 * i) / i);
    }

    auto graph1 = GraphUnit::Create(20, 120, 1130, 580, "Graph 1");
    graph1->SetValues(values1);
    window1->Push(std::move(graph1));

    manager->Push(std::move(window1));

    /* Window 2 */
    auto window2 = WindowUnit::Create(1280, 720, "Window 2");
    manager->Push(std::move(window2));

    /* Run */
    manager->Run();
}