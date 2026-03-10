#pragma once
#include <GLFW/glfw3.h>

namespace GraphTools {
    using HWINDOW = GLFWwindow*;

    struct Color {
        float m_r, m_g, m_b, m_a;
    };

    inline Color windowColor = { 0.25f, 0.35f, 0.55f, 1.0f };
}