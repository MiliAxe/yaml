/*
 *  @file application.hpp
 *
 *  @brief The model viewer state will be handled
 *  	   in this class.
 */

#pragma once

#include "camera.hpp"

#include <GLFW/glfw3.h>

class Application {
private:
  GLFWwindow *window_;
  FreeRoamCamera camera_;
  // TODO: model
  // TODO: std::vector of shaders

  static void windowSizeCallback_(GLFWwindow *window, int width,
                                  int height) noexcept;
  static void windowKeyCallback_(GLFWwindow *window, int key, int scan_code,
                                 int action, int mods) noexcept;

  void windowResize_(int width, int height) noexcept;
  void processInput_(GLFWwindow *window, int key, int action) noexcept;

  void initGLFW_();
  void initGLAD_() const;

  void setGlParams_() const noexcept;

public:
  Application();

  void init();
  void run();
};
