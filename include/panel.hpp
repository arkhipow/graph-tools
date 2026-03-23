#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <functional>
#include <memory>
#include <string>
#include <vector>

class PanelUnit {
public:
    PanelUnit(int x, int y, int width, int height) noexcept;
    virtual ~PanelUnit() = default;

    virtual void Render() = 0;

protected:
    int m_x, m_y;
    int m_w, m_h;
};

class ButtonUnit final : public PanelUnit {
public:
    [[nodiscard]] static std::unique_ptr<ButtonUnit> Create(int x, int y, int width, int height, const std::string& title);

    void Render() override;

    void SetCallback(std::function<void()> callback) noexcept { m_callback = callback; }

private:
    ButtonUnit(int x, int y, int w, int h, const std::string& title);

    std::string m_title;
    std::function<void()> m_callback;
};

class GraphUnit final : public PanelUnit {
public:
    [[nodiscard]] static std::unique_ptr<GraphUnit> Create(int x, int y, int width, int height, const std::string& title);

    void Render() override;

    void SetValues(const std::vector<float>& values);

private:
    GraphUnit(int x, int y, int w, int h, const std::string& title) noexcept;

    std::string m_title;
    std::vector<float> m_values;
};