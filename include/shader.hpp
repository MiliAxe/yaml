/*
 *  @file shader.hpp
 *
 *  @brief Basic shader class abstraction with sets
 *  	   of tools built for creation process of
 *  	   shaders.
 */
#pragma once

#include "globals.hpp"

class BaseShader {
protected:
  GLuint id_;

  [[nodiscard("value not stored")]] static auto
  readShaderSource_(const char *file_path) noexcept -> char *;
  void compile_(const char *file_path) noexcept;

public:
  BaseShader(const char *file_path, GLenum type);
  BaseShader(const BaseShader &) = delete;
  auto operator=(const BaseShader &) -> BaseShader & = delete;
  virtual ~BaseShader();

  auto getId() const noexcept -> const GLuint &;
};

class VertexShader : public BaseShader {
public:
  VertexShader(const char *file_path);
};

class FragmentShader : public BaseShader {
public:
  FragmentShader(const char *file_path);
};
