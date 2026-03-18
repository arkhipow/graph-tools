#include "panel.hpp"

PanelUnit::PanelUnit(int width, int height) : m_width(width), m_height(height) {
    m_scale = ImGui::GetIO().FontGlobalScale;
}

void PanelUnit::SetPos(int x, int y) noexcept {
    m_posX = x;
    m_posY = y;
}

PanelButton::PanelButton(int width, int height, const std::string& text) : PanelUnit(width, height), m_text(text) {
    SetPos(0, 0);
}

void PanelButton::Render() {
    ImGui::SetCursorPos(ImVec2(m_posX * m_scale, m_posY * m_scale));
    ImGui::Button(m_text.c_str(), ImVec2(m_width * m_scale, m_height * m_scale));
}