#include "cursor.hpp"

void Cursor::updatePosition(GLFWwindow * window) {
  *this = fromWindow(window);
}

auto Cursor::fromWindow(GLFWwindow * window) -> Cursor {
  double x,y;
  glfwGetCursorPos(window, &x, &y);

  Cursor cursor;
  cursor.x = static_cast<float>(x);
  cursor.y = static_cast<float>(y);

  return cursor;
}

auto Cursor::operator-(const Cursor &other) -> Cursor {
  Cursor new_cursor;
  new_cursor.x = x - other.x;
  new_cursor.y = y - other.y;

  return new_cursor;
}

auto Cursor::operator*(int coefficient) const -> Cursor {
  Cursor new_cursor;
  new_cursor.x = x * coefficient;
  new_cursor.y = y * coefficient;

  return new_cursor;
}

auto Cursor::reverse() const -> Cursor {
  return *this*-1;
}
