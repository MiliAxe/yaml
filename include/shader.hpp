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

private:
  [[nodiscard("value not stored")]] static auto
  readShaderSource_(const char *file_path) -> std::string;
  void compile_(const char *file_path) const noexcept;
  void checkErrors_(const char *file_path) const;

public:
  BaseShader(const char *file_path, GLenum type) noexcept;
  BaseShader(const BaseShader &) noexcept = delete;
  auto operator=(const BaseShader &) noexcept -> BaseShader & = delete;
  virtual ~BaseShader() noexcept;

  auto getId() const noexcept -> const GLuint &;
};

class VertexShader : public BaseShader {
public:
  VertexShader(const char *file_path) noexcept;
};

class FragmentShader : public BaseShader {
public:
  FragmentShader(const char *file_path) noexcept;
};
