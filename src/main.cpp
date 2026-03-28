#include "window.hpp"

using namespace FactoryUnit;

int main() {
    auto manager = WindowManager::Create();
    auto window = Create<WindowUnit>(Pixels(2200, 1300), "GraphTools");

    auto toolbar = Create<PanelUnit>(Percent(25, 100), "Toolbar");
    toolbar->SetColor(0.08f, 0.10f, 0.13f, 1.00f);
    for (int i = 1; i <= 5; ++i) {
        auto button = Create<ButtonUnit>(Percent(90, 4), "Button " + std::to_string(i));
        button->SetPos(Percent(5, 5 * (i - 1) + 2));
        toolbar->Push(std::move(button));
    }

    std::vector<float> v1, v2;
    for (float i = - 10; i <= 10; i += 0.1) {
        v1.push_back(std::exp(-0.2f * std::abs(i)) * std::sin(3.0f * i));
        v2.push_back(std::exp(-0.2f * std::abs(i)) * (3.0f * std::cos(3.0f * i) - 0.2f * (i > 0 ? 1.0f : -1.0f) * std::sin(3.0f * i)));
    }

    auto graphs = Create<PanelUnit>(Percent(75, 80), "Graphs");
    graphs->SetPos(Percent(25, 0));

    auto function = Create<GraphUnit>(Percent(96, 47), "Function");
    function->SetPos(Percent(2, 2));
    function->SetValues(std::move(v1));
    graphs->Push(std::move(function));

    auto derivative = Create<GraphUnit>(Percent(96, 47), "Derivative");
    derivative->SetPos(Percent(2, 51));
    derivative->SetValues(std::move(v2));
    graphs->Push(std::move(derivative));

    auto gsettings = Create<PanelUnit>(Percent(75, 20), "GSettings");
    gsettings->SetPos(Percent(25, 80));
    gsettings->SetColor(0.0f, 0.0f, 0.0f, 0.0f);

    auto csettings1 = Create<PanelUnit>(Percent(70, 100), "CSettings 1");
    csettings1->SetPos(Percent(30, 0));
    csettings1->SetColor(0.5f, 0.5f, 1.0f, 0.01f);

    auto csettings2 = Create<PanelUnit>(Percent(70, 100), "CSettings 2");
    csettings2->SetPos(Percent(30, 0));
    csettings2->SetColor(0.5f, 0.5f, 1.0f, 0.01f);

    auto drop = Create<DropListUnit>(Percent(25, 1), "##List");
    drop->SetPos(Percent(2.5, 5));
    drop->Push("Function", std::move(csettings1));
    drop->Push("Derivative", std::move(csettings2));
    gsettings->Push(std::move(drop));

    window->Push(std::move(toolbar));
    window->Push(std::move(graphs));
    window->Push(std::move(gsettings));

    manager->Push(std::move(window));
    manager->Run();
}