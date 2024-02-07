#include "cursor.hpp"

void Cursor::updatePosition(GLFWwindow *window) { *this = fromWindow(window); }

auto Cursor::fromWindow(GLFWwindow *window) -> Cursor {
  f64 x_pos;
  f64 y_pos;
  glfwGetCursorPos(window, &x_pos, &y_pos);

  Cursor cursor;
  cursor.x_ = static_cast<f32>(x_pos);
  cursor.y_ = static_cast<f32>(y_pos);

  return cursor;
}

auto Cursor::operator-(const Cursor &rhs) const -> Cursor {
  Cursor new_cursor;

  new_cursor.x_ = x_ - rhs.x_;
  new_cursor.y_ = y_ - rhs.y_;

  return new_cursor;
}
