![Sample](assets/sample.png)

```cpp
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

    std::vector<float> values;
    for (float i = -10; i <= 10; i += 0.1) {
        values.push_back(std::sin(2 * i) / i);
    }

    auto graph = UnitFactory::Create<GraphUnit>(1160, 580, "Graph");
    graph->SetPos(20, 120);
    graph->SetValues(std::move(values));

    window->Push(std::move(button));
    window->Push(std::move(graph));

    manager->Push(std::move(window));

    /* Run */
    manager->Run();
}