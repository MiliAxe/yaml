/*
 * @file vbo.hpp
 *
 * @brief Vertex Buffer Object (VBO) class
 *
 */

#pragma once

#include "globals.hpp"
#include "vertex.hpp"

#include <vector>

class VBO {
private:
  GLuint id_;

public:
  VBO() noexcept;

  void  bind() const noexcept;
  static void unbind()  noexcept;
  void setData(const std::vector<Vertex> &data) const noexcept;
  void deleteBuffer() const noexcept;
};
