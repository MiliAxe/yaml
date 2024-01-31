/*
 *  @file shader.hpp
 *
 *  @brief Basic shader class abstraction with sets
 *  	   of tools built for creation process of
 *  	   shaders.
 */
#pragma once

#include "globals.hpp"

class Shader {

  friend class ShaderProgram;

private:
  GLuint id_;
  GLenum type_;
  std::string type_name_;
  std::string file_path_;

  [[nodiscard("return value unused")]] static auto
  readShaderSource_(const char *file_path) noexcept -> char *;

  void create_(GLenum type, const char *file_path) const noexcept;
  auto checkErrors_() const noexcept -> bool;

public:
  Shader(GLenum type, const char *file_path);
  Shader(const Shader &) = delete;
  auto operator=(const Shader &) -> Shader & = delete;
  ~Shader();

  void deleteShader() const noexcept;
  [[nodiscard("variable unused.")]] auto getId() const noexcept
      -> const GLuint &;
};
