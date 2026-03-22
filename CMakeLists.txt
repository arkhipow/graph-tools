cmake_minimum_required(VERSION 4.3.0)

project(GraphTools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

add_library(glad STATIC
    ${GLAD_DIR}/src/glad.c
)

target_include_directories(glad PUBLIC
    ${GLAD_DIR}/include
)

# GLFW
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "Build the GLFW test programs"    FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "Build the GLFW documentation"    FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "Generate installation target"    FORCE)

add_subdirectory(${GLFW_DIR})

# ImGUI
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLFW_DIR}/include
)

# GraphTools
set(GRAPH_TOOLS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(graph_tools
    ${GRAPH_TOOLS_DIR}/src/panel.cpp
    ${GRAPH_TOOLS_DIR}/src/window.cpp
    ${GRAPH_TOOLS_DIR}/src/main.cpp
)

target_include_directories(graph_tools PRIVATE
    ${GRAPH_TOOLS_DIR}/include
)

target_link_libraries(graph_tools PRIVATE
    ${OPENGL_LIBRARIES}
    glad
    glfw
    imgui
)