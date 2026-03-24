#pragma once

#include "factory.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <functional>
#include <string>

class PanelUnit : ObjectUnit {
public:
    PanelUnit(int width, int height, std::string title);
    virtual ~PanelUnit() = default;

    virtual void Render() = 0;

    void SetPos(int x, int y) noexcept { m_x = x; m_y = y; }
    void SetSize(int width, int height) noexcept { m_w = width; m_h = height; }

protected:
    void SetLayout() const;

    int m_w, m_h;
    int m_x, m_y;
    std::string m_title;
};

class ButtonUnit final : public PanelUnit {
public:
    ButtonUnit(int width, int height, std::string title);

    void Render() override;

    void SetCallback(std::function<void()> callback) { m_callback = callback; }

private:
    std::function<void()> m_callback;
};