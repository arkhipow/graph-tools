![Sample](assets/sample.png)

```cpp
#include "window.hpp"

using namespace FactoryUnit;

int main() {
    auto manager = WindowManager::Create();
    auto window = Create<WindowUnit>(Pixels(1280, 720), "Graph Tools");

    auto toolbar = Create<PanelUnit>(Percent(30, 100), "Toolbar");
    for (int i = 1; i <= 5; ++i) {
        toolbar->Push(Create<ButtonUnit>(Percent(100, 20), "Button " + std::to_string(i)));
    }

    std::vector<float> v1, v2;
    for (float i = -10.0f; i <= 10.0f; i += 0.1f) {
        v1.push_back(std::abs(i) < 0.001f ? 2.0f : std::sin(2 * i) / i);
        v2.push_back(std::exp(-0.1f * std::abs(i)) * std::cos(2.0f * i));
    }

    auto panel = Create<PanelUnit>(Percent(70, 100), "Panel");
    panel->SetPos(Percent(30, 0));

    auto g1 = Create<GraphUnit>(Percent(100, 50), "Graph 1");
    auto g2 = Create<GraphUnit>(Percent(100, 50), "Graph 2");

    g1->SetValues(std::move(v1));
    g2->SetValues(std::move(v2));
    g2->SetPos(Percent(0, 50));

    panel->Push(std::move(g1));
    panel->Push(std::move(g2));
    window->Push(std::move(toolbar));
    window->Push(std::move(panel));

    manager->Push(std::move(window));
    manager->Run();
}