#include <GLFW/glfw3.h>
class Cursor {
public:
  Cursor() = default;
  void updatePosition(GLFWwindow *);
  auto getPitch() -> float;
  auto operator-(const Cursor &) -> Cursor;
  auto operator*(int) const -> Cursor;
  auto reverse() const -> Cursor;
  static auto fromWindow(GLFWwindow * window) -> Cursor;
private:
  float x, y;
  friend class FreeRoamCamera;
  friend class CameraTransform;
};
