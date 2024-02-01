/*
 * @file ebo.hpp
 *
 * @brief This file contains the declaration of the EBO (Element Buffer Object)
 * class
 *
 */

#pragma once
#include <glad/glad.h>
#include <vector>

class EBO {
private:
  GLuint id_;

public:
  EBO() noexcept;

  void bind() const noexcept;
  static void unbind() noexcept;
  void deleteBuffer() const noexcept;
  void setData(const std::vector<GLuint> &indices) const noexcept;
};
