#include "panel.hpp"

PanelUnit::PanelUnit(int width, int height, std::string title)
    : m_w(width), m_h(height), m_x(0), m_y(0), m_title(std::move(title)) {}

void PanelUnit::SetLayout() const {
    ImGui::SetCursorPos(ImVec2(m_x, m_y));
}

ButtonUnit::ButtonUnit(int width, int height, std::string title)
    : PanelUnit(width, height, std::move(title)), m_callback(nullptr) {}

void ButtonUnit::Render() {
    SetLayout();

    if (ImGui::Button(m_title.c_str(), ImVec2(m_w, m_h))) {
        if (m_callback) { m_callback(); };
    }
};