/*
 *
 * @file vao.hpp
 *
 * @brief Vertex Array Object (VAO) class
 *
 */

#pragma once
#include <globals.hpp>
#include <vbo.hpp>

class VAO {
private:
  GLuint id_;

public:
  VAO();

  void bind();
  static void unbind();
  void deleteArray();
  void linkVBO(VBO &vbo, uint8 slot, uint8 n_components, GLenum type,
               uint8 stride, uint8 offset);
};
