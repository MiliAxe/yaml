#pragma once

#include "globals.hpp"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace fn {

GLFWwindow *createGLFWwindow();
void bindGLBindings();
GLFWwindow *initGLFWandGLAD();

} // namespace fn
