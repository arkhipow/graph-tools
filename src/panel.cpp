#include "panel.hpp"

void IPanelUnit::SetLayout() const {
    if (m_pos) {
        std::pair<float, float> pos = m_pos->GetMeasure();
        ImGui::SetCursorPos(ImVec2(pos.first, pos.second));
    }
}

void PanelUnit::Push(std::unique_ptr<IPanelUnit> unit) {
    m_units.push_back(std::move(unit));
}

void PanelUnit::Render() {
    auto [w, h] = m_size->GetMeasure();

    if (m_pos) {
        auto [x, y] = m_pos->GetMeasure();
        ImGui::SetCursorPos(ImVec2(x, y));
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

    ImGui::BeginChild(m_title.c_str(), ImVec2(w, h), false);

    for (auto& it : m_units) {
        it->Render();
    }

    ImGui::EndChild();

    ImGui::PopStyleVar(2);
}

void ButtonUnit::Render() {
    SetLayout();

    std::pair<float, float> size = m_size->GetMeasure();
    if (ImGui::Button(m_title.c_str(), ImVec2(size.first, size.second))) {
        if (m_callback) { m_callback(); };
    }
};

void GraphUnit::Render() {
    SetLayout();

    std::pair<float, float> size = m_size->GetMeasure();
    ImGui::PlotLines(m_title.c_str(), m_values.data(), m_values.size(), 0, nullptr, FLT_MAX, FLT_MAX, ImVec2(size.first, size.second));
}