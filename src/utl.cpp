#include "utl.hpp"
#include "globals.hpp"
#include <GLFW/glfw3.h>

GLFWwindow *fn::createGLFWwindow() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *new_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                            "Develop window", nullptr, nullptr);

  if (nullptr == new_window) {
    glfwTerminate();
    throw RUNTIME_ERROR;
  }

  return new_window;
}

void fn::bindGLBindings() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    ERROR_LOG("failed binding glad.");
    throw RUNTIME_ERROR;
  }
}

GLFWwindow *fn::initGLFWandGLAD() {
  if (!glfwInit()) {
    ERROR_LOG("failed initializing GLFW.");
  }

  GLFWwindow *window = createGLFWwindow();
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  bindGLBindings();

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetWindowSizeCallback(
      window,
      []([[maybe_unused]] GLFWwindow *window, int width,
         int height) noexcept -> void { glViewport(0, 0, width, height); });

  glfwSetKeyCallback(window,
                     [](GLFWwindow *window, int key,
                        [[maybe_unused]] int scan_code, int action,
                        [[maybe_unused]] int mods) noexcept -> void {
                       if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                         glfwSetWindowShouldClose(window, 1);
                       }
                     });

  return window;
}
