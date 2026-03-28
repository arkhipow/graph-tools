#include "panel.hpp"

void IPanelUnit::SetLayout() const {
    if (m_pos) {
        std::pair<float, float> pos = m_pos->GetMeasure();
        ImVec2 pad = ImGui::GetStyle().WindowPadding;
        ImGui::SetCursorPos(ImVec2(pos.first + pad.x, pos.second + pad.y));
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

    if (m_custom) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, m_color);
    }

    auto [paddingX, paddingY] = m_padding->GetMeasure();
    auto [spacingX, spacingY] = m_spacing->GetMeasure();

    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(paddingX, paddingY));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacingX, spacingY));

    if (ImGui::BeginChild(m_title.c_str(), ImVec2(w, h), false)) {
        for (auto& it : m_units) {
            it->Render();
        }

        ImGui::EndChild();
    }

    ImGui::PopStyleVar(4);

    if (m_custom) {
        ImGui::PopStyleColor();
    }
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

    if (ImPlot::BeginPlot((m_title + " Plot").c_str(), ImVec2(size.first, size.second))) {
        ImPlot::PlotLine(m_title.c_str(), m_values.data(), m_values.size());
        ImPlot::EndPlot();
    }
}

void DropListUnit::Render() {
    if (m_units.empty()) { return; }

    SetLayout();
    auto [w, h] = m_size->GetMeasure();

    std::vector<std::string> list;
    for (const auto& [title, _] : m_units) {
        list.push_back(title);
    }

    ImGui::SetNextItemWidth(w);
    if (ImGui::BeginCombo(m_title.c_str(), list[m_current].c_str())) {
        for (int i = 0; i < list.size(); ++i) {
            const bool isSelected = (m_current == i);
            
            if (ImGui::Selectable(list[i].c_str(), isSelected)) {
                m_current = i;
            }

            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    for (auto& unit : m_units[list[m_current]]) {
        unit->Render();
    }
}

void DropListUnit::Push(std::string title, std::unique_ptr<PanelUnit> unit) {
    m_units[title].push_back(std::move(unit));
}