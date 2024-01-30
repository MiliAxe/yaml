cmake_minimum_required(VERSION 3.20)

project(imgui)

# Add all source files in the ImGui directory
file(
  GLOB
  IMGUI_BACKEND_SOURCE
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h")

file(GLOB IMGUI_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp")

# Create the ImGui library target
add_library(imgui SHARED ${IMGUI_SOURCE} ${IMGUI_BACKEND_SOURCE})

# Include directories for the ImGui library
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui/")
# "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/")
