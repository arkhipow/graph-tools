#include "utils.hpp"

std::pair<float, float> MeasurePercentUnit::GetMeasure() {
    ImVec2 size = ImGui::GetWindowContentRegionMax();

    float x = size.x * (m_x / 100);
    float y = size.y * (m_y / 100);

    return { x, y };
}