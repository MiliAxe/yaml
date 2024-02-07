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

  class Mouse {
  public:
    Mouse() = default;

    auto mousePressReturnOffset(GLFWwindow *window) -> Cursor;
    void mouseRelease(GLFWwindow *window);

  private:
    Cursor last_cursor_;
    bool first_click_ = true;
  };

private:
  GLFWwindow *window_;
  FreeRoamCamera camera_;
  Mouse mouse;
  f32 delta_time_;

  static void windowSizeCallback_(GLFWwindow *window, int32 width,
                                  int32 height) noexcept;
  static void windowKeyCallback_(GLFWwindow *window, int32 key, int32 scan_code,
                                 int32 action, int32 mods) noexcept;

  void windowResize_(f32 width, f32 height) noexcept;
  void processInput_() noexcept;

  void init_();
  void initGLFW_();
  void initGLAD_() const;

  void setGlParams_() const noexcept;

  void updateDeltaTime_() noexcept;
  void update_() noexcept;

public:
  Application() noexcept;
  Application(const Application &other) = delete;
  auto operator=(const Application &other) -> Application & = delete;
  virtual ~Application() noexcept;

  void run();
};
