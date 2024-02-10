#include "cursor.hpp"

Cursor::Cursor(f32 x, f32 y) : x(x), y(y) {}

void Cursor::updatePosition(GLFWwindow *window) { *this = fromWindow(window); }

auto Cursor::fromWindow(GLFWwindow *window) -> Cursor {
  f64 x_pos;
  f64 y_pos;
  glfwGetCursorPos(window, &x_pos, &y_pos);

  Cursor cursor;
  cursor.x = static_cast<f32>(x_pos);
  cursor.y = static_cast<f32>(y_pos);

  return cursor;
}

auto Cursor::operator-(const Cursor &rhs) const -> Cursor {
  Cursor new_cursor;

  new_cursor.x = x - rhs.x;
  new_cursor.y = y - rhs.y;

  return new_cursor;
}
