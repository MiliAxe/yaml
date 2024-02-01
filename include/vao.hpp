/*
 *
 * @file vao.hpp
 *
 * @brief Vertex Array Object (VAO) class
 *
 */

#pragma once

#include "globals.hpp"
#include "vbo.hpp"

class VAO {
private:
  GLuint id_;

public:
  VAO() noexcept;

  void bind() const noexcept;
  static void unbind() noexcept;
  void deleteArray() const noexcept;
  void linkVBO(VBO &vbo, uint8 slot, uint8 n_components, GLenum type,
               uint8 stride, uint8 offset) const noexcept;
};
