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
  class Mouse {
  public:
    auto mousePressReturnOffset(GLFWwindow * window) -> Cursor;
    void mouseRelease(GLFWwindow * window);
  private:
    Cursor last_cursor_;
    bool first_click_ = true;
  };
  Mouse mouse;

  float delta_time_;

  // TODO: model
  // TODO: std::vector of shaders

  static void windowSizeCallback_(GLFWwindow *window, int width,
                                  int height) noexcept;
  static void windowKeyCallback_(GLFWwindow *window, int key, int scan_code,
                                 int action, int mods) noexcept;

  void windowResize_(float width, float height) noexcept;
  void processKeyboardInput_() noexcept;
  void processMouseInput_() noexcept;

  void init_();
  void initGLFW_();
  void initGLAD_() const;

  void setGlParams_() const noexcept;

  void updateDeltaTime_() noexcept;
  void update_() noexcept;

public:
  Application();

  void run();
};
