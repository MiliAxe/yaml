#include "application.hpp"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// ######################### GLFW window callbacks #############################

void Application::windowSizeCallback_(GLFWwindow *window, int width,
                                      int height) noexcept {
  Application *instance =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  instance->windowResize_(width, height);
}

void Application::windowKeyCallback_(GLFWwindow *window, int key, int scan_code,
                                     int action, int mods) noexcept {
  Application *instance =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  instance->processInput_(window, key, action);
}

// ##############################################################################

void Application::windowResize_(int width, int height) noexcept {
  glViewport(0, 0, width, height);
  camera_.setApsectRatio(width / static_cast<float>(height));
}

void Application::processInput_(GLFWwindow *window, int key,
                                int action) noexcept {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

void Application::initGLFW_() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if (!glfwInit()) {
    ERROR_LOG("Failed to init GLFW.");
    throw RUNTIME_ERROR;
  }

  window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Develop window",
                             nullptr, nullptr);
  if (nullptr == window_) {
    ERROR_LOG("GLFW window is null.");
    glfwTerminate();
    throw RUNTIME_ERROR;
  }

  glfwMakeContextCurrent(window_);
  glfwSwapInterval(1);

  glfwSetWindowSizeCallback(window_, windowSizeCallback_);
  glfwSetKeyCallback(window_, windowKeyCallback_);
}

void Application::initGLAD_() const {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    ERROR_LOG("Failed binding glad.");
    throw RUNTIME_ERROR;
  }
}

void Application::setGlParams_() const noexcept {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Application::updateDeltaTime_() noexcept {
  float current_time = static_cast<float>(glfwGetTime());
  static float last_time;
  delta_time_ = current_time - last_time;
  last_time = current_time;
}

void Application::update_() noexcept { updateDeltaTime_(); }

Application::Application() {
  glfwSetWindowUserPointer(window_, reinterpret_cast<void *>(this));
}

void Application::init() {
  initGLFW_();
  initGLAD_();
  setGlParams_();
}

void Application::run() {
  glClearColor(0, 0, 0, 0);
  while (!glfwWindowShouldClose(window_)) {
    glClear(GL_COLOR_BUFFER_BIT);

    update_();

    glfwPollEvents();
    glfwSwapBuffers(window_);
  }
}
