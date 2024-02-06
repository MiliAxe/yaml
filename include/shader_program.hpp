/*
 *  @file shader_program.hpp
 *
 *  @brief Tools for shader program that are going to
 *   	   be used during the graphcis pipeline.
 *
 */

#pragma once

#include "globals.hpp"

#include <glad/glad.h>
#include <glm/ext.hpp>

class ShaderProgram {
private:
  GLuint id_;

  void checkErrors_() const;

public:
  ShaderProgram(const char *vertex_path, const char *fragment_path) noexcept;

  static void deActive() noexcept;
  void activate() const noexcept;
  void deleteProgram() const noexcept;

  void setBool(const char *name, bool value) const noexcept;
  void setInt(const char *name, int32 value) const noexcept;
  void setFloat(const char *name, f32 value) const noexcept;
  void setVec2(const char *name, const glm::vec2 &value) const noexcept;
  void setVec2(const char *name, f32 x, f32 y) const noexcept;
  void setVec3(const char *name, const glm::vec3 &value) const noexcept;
  void setVec3(const char *name, f32 x, f32 y, f32 z) const noexcept;
  void setVec4(const char *name, const glm::vec4 &value) const noexcept;
  void setVec4(const char *name, f32 x, f32 y, f32 z, f32 w) const noexcept;
  void setMat2(const char *name, const glm::mat2 &matrix) const noexcept;
  void setMat3(const char *name, const glm::mat3 &matrix) const noexcept;
  void setMat4(const char *name, const glm::mat4 &matrix) const noexcept;

  [[nodiscard]] auto getId() const noexcept -> const GLuint &;
};
