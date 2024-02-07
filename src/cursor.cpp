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

auto Cursor::operator-(const Cursor &rhs) -> Cursor {
  Cursor new_cursor;

  new_cursor.x_ -= x_ - rhs.x_;
  new_cursor.y_ -= y_ - rhs.y_;

  return new_cursor;
}
