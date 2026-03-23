#include "panel.hpp"

PanelUnit::PanelUnit(int x, int y, int width, int height) noexcept : m_x(x), m_y(y), m_w(width), m_h(height) {}

ButtonUnit::ButtonUnit(int x, int y, int w, int h, const std::string& title) : PanelUnit(x, y, w, h), m_title(title), m_callback(nullptr) {}

std::unique_ptr<ButtonUnit> ButtonUnit::Create(int x, int y, int width, int height, const std::string& title) {
    return std::unique_ptr<ButtonUnit>(new ButtonUnit(x, y, width, height, title));
}

void ButtonUnit::Render() {
    ImGui::SetCursorPos(ImVec2(m_x, m_y));
    if (ImGui::Button(m_title.c_str(), ImVec2(m_w, m_h))) {
        m_callback();
    }
}

GraphUnit::GraphUnit(int x, int y, int w, int h, const std::string& title) noexcept : PanelUnit(x, y, w, h), m_title(title) {}

std::unique_ptr<GraphUnit> GraphUnit::Create(int x, int y, int width, int height, const std::string& title) {
    return std::unique_ptr<GraphUnit>(new GraphUnit(x, y, width, height, title));
}

void GraphUnit::Render() {
    ImGui::SetCursorPos(ImVec2(m_x, m_y));
    ImGui::PlotLines(m_title.c_str(), m_values.data(), m_values.size(), 0, nullptr, FLT_MAX, FLT_MAX, ImVec2(m_w, m_h));
}

void GraphUnit::SetValues(const std::vector<float>& values) {
    m_values = values;
}