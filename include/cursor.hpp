#include "globals.hpp"

#include <GLFW/glfw3.h>

class Cursor {

  friend class FreeRoamCamera;
  friend class CameraTransform;

private:
  f32 x_;
  f32 y_;

public:
  Cursor() = default;

  static auto fromWindow(GLFWwindow *window) -> Cursor;

  auto operator-(const Cursor &rhs) const -> Cursor;

  void updatePosition(GLFWwindow *window);
  auto getPitch() -> f32;
  auto reverse() const -> Cursor;
};
