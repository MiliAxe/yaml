cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(yaml)

add_subdirectory(lib)

add_executable(model_loader)
target_sources(model_loader PRIVATE src/main.cpp)
target_include_directories(model_loader
                           PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(model_loader PRIVATE glfw glad stb_image)
