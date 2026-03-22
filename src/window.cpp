#include "window.hpp"

#include <stdexcept>

WindowUnit::WindowUnit(GLFWwindow* handle) : m_handle(handle) {
    m_context = ImGui::CreateContext();
}

std::unique_ptr<WindowUnit> WindowUnit::Create(int width, int height, const std::string& title) {
    GLFWwindow* handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!handle) {
        throw (std::runtime_error("Failed to create GLFW window"));
    }

    static bool isLoaded = false;
    if (!isLoaded) {
        glfwMakeContextCurrent(handle);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw (std::runtime_error("Failed to load OpenGL functions"));
        }
        isLoaded = true;
    }

    auto unit = std::unique_ptr<WindowUnit>(new WindowUnit(handle));

    ImGui::SetCurrentContext(unit->GetContext());

    unit->SetScale();

    ImGui_ImplGlfw_InitForOpenGL(handle, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return unit;
}

WindowUnit::~WindowUnit() {
    glfwMakeContextCurrent(m_handle);
    ImGui::SetCurrentContext(m_context);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext(m_context);
    glfwDestroyWindow(m_handle);
}

void WindowUnit::Render() {
    NewFrame();

    ImGui::Begin("Render");
    ImGui::End();

    EndFrame();
}

void WindowUnit::NewFrame() {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}

void WindowUnit::EndFrame() {
    ImGui::Render();

    int w, h;
    glfwGetFramebufferSize(m_handle, &w, &h);
    glViewport(0, 0, w, h);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_handle);
}

void WindowUnit::SetScale() {
    float scale;
    glfwGetWindowContentScale(m_handle, &scale, nullptr);

    ImGuiIO& io = ImGui::GetIO();

    io.IniFilename = nullptr;

    ImGui::GetStyle().ScaleAllSizes(scale);

    io.Fonts->Clear();
    ImFontConfig cfg;
    cfg.SizePixels = 13.0f * scale;
    io.Fonts->AddFontDefault(&cfg);
}

bool WindowManager::m_isCreated = false;

WindowManager::WindowManager() {
    if (!glfwInit()) {
        throw (std::runtime_error("Failed to initialize GLFW"));
    }

    IMGUI_CHECKVERSION();
}

std::unique_ptr<WindowManager> WindowManager::Create() {
    if (m_isCreated) {
        throw (std::runtime_error("Failed to create window manager"));
    }

    m_isCreated = true;
    return std::unique_ptr<WindowManager>(new WindowManager);
}

WindowManager::~WindowManager() {
    m_units.clear();

    glfwTerminate();
    m_isCreated = false;
}

void WindowManager::Push(std::unique_ptr<WindowUnit> unit) {
    m_units.push_back(std::move(unit));
}

void WindowManager::Run() {
    while (!m_units.empty()) {
        glfwPollEvents();

        for (auto& unit : m_units) {
            if (glfwWindowShouldClose(unit->GetHandle())) {
                continue;
            }

            UpdateContext(unit.get());
            unit->Render();
        }

        m_units.erase(
            std::remove_if(m_units.begin(), m_units.end(),
                [](auto& u) { return glfwWindowShouldClose(u->GetHandle()); }),
            m_units.end()
        );
    }
}

void WindowManager::UpdateContext(WindowUnit* unit) {
    if (glfwGetCurrentContext() != unit->GetHandle()) {
        glfwMakeContextCurrent(unit->GetHandle());
    }

    if (ImGui::GetCurrentContext() != unit->GetContext()) {
        ImGui::SetCurrentContext(unit->GetContext());
    }
}