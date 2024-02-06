#include "application.hpp"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// ######################### GLFW window callbacks #############################

void Application::windowSizeCallback_(GLFWwindow *window, int width,
                                      int height) noexcept {
  Application *instance =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  glViewport(0, 0, width, height);
  instance->windowResize_(width, height);
}

void Application::windowResize_(float width, float height) noexcept {
  camera_.setApsectRatio(width / height);
}

void Application::windowKeyCallback_(GLFWwindow *window, int key,
                                     [[maybe_unused]] int scan_code, int action,
                                     [[maybe_unused]] int mods) noexcept {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

// ##############################################################################

void Application::processKeyboardInput_() noexcept {

  auto new_position = camera_.getPosition();
  float delta_speed = camera_.getSpeed() * delta_time_;
  if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
    new_position += delta_speed * camera_.getDirection();
  }
  if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
    new_position -= delta_speed * camera_.getDirection();
  }
  if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
    new_position +=
        delta_speed *
        glm::normalize(glm::cross(camera_.getDirection(), camera_.getUp()));
  }
  if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
    new_position -=
        delta_speed *
        glm::normalize(glm::cross(camera_.getDirection(), camera_.getUp()));
  }
  if (glfwGetKey(window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    camera_.setSpeed(INITIAL_CAM_SPEED * 3.0f);
  }
  if (glfwGetKey(window_, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    camera_.setSpeed(INITIAL_CAM_SPEED);
  }
  camera_.setPosition(new_position);
}

void Application::processMouseInput_() noexcept {
  if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double current_x;
    double current_y;
    glfwGetCursorPos(window_, &current_x, &current_y);

    camera_.updateYawAndPitch(current_x, current_y);

  } else if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    camera_.setFirstMove(true);
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

void Application::update_() noexcept {
  updateDeltaTime_();
  processKeyboardInput_();
  processMouseInput_();
  camera_.update();
}

Application::Application() {
  init_();
  glfwSetWindowUserPointer(window_, reinterpret_cast<void *>(this));
}

void Application::init_() {
  initGLFW_();
  initGLAD_();
  setGlParams_();
}

void Application::run() {
  glClearColor(0, 0, 0, 0);
  while (!glfwWindowShouldClose(window_)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update_();

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}
