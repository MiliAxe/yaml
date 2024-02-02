/*
 *  @file Vertex.hpp
 *
 *  @brief Vertex structure.
 *
 */

#pragma once

#include <glm/ext.hpp>

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 uv;
};
