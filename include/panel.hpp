#pragma once

#include "factory.hpp"

#include <functional>
#include <string>

class IPanelUnit : public IObjectUnit {
public:
    IPanelUnit(std::unique_ptr<IMeasureUnit> size, std::string title)
        : m_size(std::move(size)), m_title(std::move(title)) {}

    virtual ~IPanelUnit() = default;

    virtual void Render() = 0;

    void SetSize(std::unique_ptr<IMeasureUnit> size) noexcept { m_size = std::move(size); }
    void SetPos(std::unique_ptr<IMeasureUnit> pos) noexcept { m_pos = std::move(pos); }

protected:
    void SetLayout() const;

    std::unique_ptr<IMeasureUnit> m_size;
    std::unique_ptr<IMeasureUnit> m_pos;
    std::string m_title;
};

class PanelUnit final : public IPanelUnit {
public:
    PanelUnit(std::unique_ptr<IMeasureUnit> size, std::string title)
        : IPanelUnit(std::move(size), std::move(title)) {}

    void Push(std::unique_ptr<IPanelUnit> unit);
    void Render() override;

private:
    VectorUnique<IPanelUnit> m_units;
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