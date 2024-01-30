/*
 *
 * @file vao.hpp
 *
 * @brief Vertex Array Object (VAO) class
 *
 */

#pragma once
#include <vbo.hpp>
#include <globals.hpp>

class VAO {
private:
  GLuint id_;

public:
  VAO();

  void bind();
  static void unbind();
  void deleteArray();
  void linkVBO(const VBO &vbo, uint8 slot, uint8 n_components, GLenum type,
               uint8 stride, uint8 offset);
};
