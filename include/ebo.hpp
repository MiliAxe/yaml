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
  EBO();

  void bind();
  static void unbind();
  void deleteBuffer();
  void setData(const std::vector<GLuint> &indices);
};