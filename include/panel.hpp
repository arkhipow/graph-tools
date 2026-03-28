#pragma once

#include "factory.hpp"

#include <implot.h>

#include <functional>
#include <string>

class IPanelUnit : public IObjectUnit {
public:
    IPanelUnit(std::unique_ptr<IMeasureUnit> size, std::string title)
        : m_size(std::move(size)), m_title(std::move(title)),
        m_pos(FactoryUnit::Pixels(0, 0)),
        m_padding(FactoryUnit::Pixels(0, 0)),
        m_spacing(FactoryUnit::Pixels(0, 0)) {}

    virtual ~IPanelUnit() = default;

    virtual void Render() = 0;

    void SetSize(std::unique_ptr<IMeasureUnit> size) noexcept { m_size = std::move(size); }
    void SetPos(std::unique_ptr<IMeasureUnit> pos) noexcept { m_pos = std::move(pos); }

    void SetPadding(std::unique_ptr<IMeasureUnit> padding) noexcept { m_padding = std::move(padding); }
    void SetSpacing(std::unique_ptr<IMeasureUnit> spacing) noexcept { m_spacing = std::move(spacing); }

protected:
    void SetLayout() const;

    std::unique_ptr<IMeasureUnit> m_size;
    std::unique_ptr<IMeasureUnit> m_pos;
    std::unique_ptr<IMeasureUnit> m_padding;
    std::unique_ptr<IMeasureUnit> m_spacing;
    std::string m_title;
};

class PanelUnit final : public IPanelUnit {
public:
    PanelUnit(std::unique_ptr<IMeasureUnit> size, std::string title)
        : IPanelUnit(std::move(size), std::move(title)), m_custom(false) {}

    void Push(std::unique_ptr<IPanelUnit> unit);
    void Render() override;

    void SetColor(float r, float g, float b, float a) noexcept { 
        m_color = { r, g, b, a };
        m_custom = true;
    }

private:
    VectorUnique<IPanelUnit> m_units;
    ImVec4 m_color;
    bool m_custom;
};

class ButtonUnit final : public IPanelUnit {
public:
    ButtonUnit(std::unique_ptr<IMeasureUnit> size, std::string title)
        : IPanelUnit(std::move(size), std::move(title)) {}

    void Render() override;

    void SetCallback(std::function<void()> callback) { m_callback = callback; }

private:
    std::function<void()> m_callback;
};

class GraphUnit final : public IPanelUnit {
public:
    GraphUnit(std::unique_ptr<IMeasureUnit> size, std::string title)
        : IPanelUnit(std::move(size), std::move(title)) {}

    void Render() override;

    void SetValues(std::vector<float>&& values) noexcept { m_values = std::move(values); }

private:
    std::vector<float> m_values;
};