#pragma once
#include "utils.hpp"
#include <string>

namespace GraphTools {
    class Window final {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void Run();

    private:
        static void ClearFrame(HWINDOW hWnd);

        /* Callback methods */
        static void ResizeCallback(HWINDOW hWnd, int width, int height);

        HWINDOW m_hWnd;
    };
}