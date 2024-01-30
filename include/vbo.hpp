/*
 * @file vbo.hpp
 *
 * @brief Vertex Buffer Object (VBO) class
 *
 */

#pragma once
#include <globals.hpp>

class VBO {
private:
  GLuint id_;

public:
  VBO();

  void bind();
  static void unbind();
  void setData(const std::vector<Vertex> &data);
};
