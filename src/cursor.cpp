#include "cursor.hpp"

void Cursor::updatePosition(GLFWwindow *window) { *this = fromWindow(window); }

auto Cursor::fromWindow(GLFWwindow *window) -> Cursor {
  f64 x, y;
  glfwGetCursorPos(window, &x, &y);

  Cursor cursor;
  cursor.x_ = static_cast<f32>(x);
  cursor.y_ = static_cast<f32>(y);

  return cursor;
}

auto Cursor::operator-(const Cursor &other) -> Cursor {
  Cursor new_cursor;
  new_cursor.x_ -= other.x_;
  new_cursor.y_ -= other.y_;

  return new_cursor;
}
