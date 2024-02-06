cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

project(
  yaml
  VERSION 0.0.1
  LANGUAGES C CXX
  DESCRIPTION "yet another model loader in C++")

add_subdirectory(lib/)

add_executable(model_loader)
target_sources(
  model_loader
  PRIVATE src/main.cpp
          src/ebo.cpp
          src/vbo.cpp
          src/vao.cpp
          src/shader.cpp
          src/shader_program.cpp
          src/texture2d.cpp
          src/camera.cpp)
target_include_directories(model_loader
                           PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(model_loader PRIVATE glfw glad stb_image)
