#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>

class PanelUnit {
public:
    PanelUnit(int width, int height);

    virtual void Render() = 0;

    void SetPos(int x, int y) noexcept;

protected:
    int m_posX;
    int m_posY;

    int m_width;
    int m_height;

    float m_scale;
};

class PanelButton final : public PanelUnit {
public:
    PanelButton(int width, int height, const std::string& text);

    void Render() override;

private:
    std::string m_text;
};