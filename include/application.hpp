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
  OrbitalCamera orbit_cam_;
  FreeRoamCamera free_cam_;
  BaseCamera *currentCamera_ = &orbit_cam_;
  f32 delta_time_;

  static void windowSizeCallback_(GLFWwindow *window, int32 width,
                                  int32 height) noexcept;
  static void windowKeyCallback_(GLFWwindow *window, int32 key, int32 scan_code,
                                 int32 action, int32 mods) noexcept;
  static void initGLAD_();
  static void setGlParams_() noexcept;

  void windowResize_(f32 width, f32 height) noexcept;
  void keyCallbacks(int32 key, int32 action) noexcept;
  void processInput_() noexcept;

  void init_();
  void initGLFW_();

  void updateDeltaTime_() noexcept;
  void update_() noexcept;

public:
  Application() noexcept;
  Application(const Application &other) = delete;
  auto operator=(const Application &other) -> Application & = delete;
  virtual ~Application() noexcept;

  void run();
};
