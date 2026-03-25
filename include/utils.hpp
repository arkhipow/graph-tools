#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <utility>
#include <memory>
#include <vector>

template <typename T>
using VectorUnique = std::vector<std::unique_ptr<T>>;

class IObjectUnit {
public:
    IObjectUnit() = default;
    virtual ~IObjectUnit() = default;

    virtual void Render() = 0;

    IObjectUnit(const IObjectUnit&) = delete;
    IObjectUnit& operator=(const IObjectUnit&) = delete;
};

class IMeasureUnit {
public:
    IMeasureUnit(float x, float y) noexcept : m_x(x), m_y(y) {}
    virtual ~IMeasureUnit() = default;

    virtual std::pair<float, float> GetMeasure() = 0;

    IMeasureUnit(const IMeasureUnit&) = delete;
    IMeasureUnit& operator=(const IMeasureUnit&) = delete;

protected:
    float m_x, m_y;
};

class MeasurePixelUnit final : public IMeasureUnit {
public:
    MeasurePixelUnit(float x, float y) noexcept
        : IMeasureUnit(x, y) {}

    std::pair<float, float> GetMeasure() override {
        return { m_x, m_y };
    }
};

class MeasurePercentUnit final : public IMeasureUnit {
public:
    MeasurePercentUnit(float x, float y) noexcept
        : IMeasureUnit(x, y) {}

    std::pair<float, float> GetMeasure() override;
};