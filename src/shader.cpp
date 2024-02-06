#include "shader.hpp"
#include "globals.hpp"

#include <fstream>
#include <ios>
#include <sys/types.h>

auto BaseShader::readShaderSource_(const char *file_path) -> std::string {
  std::ifstream file(file_path, std::ios::binary);

  if (!file.is_open()) {
    ERROR_LOG(std::format("file \"{}\" could not be oppened.", file_path));
    throw RUNTIME_ERROR;
  }

  std::string file_string((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());

  file.close();

  return file_string;
}

BaseShader::BaseShader(const char *file_path, GLenum type) noexcept {
  id_ = glCreateShader(type);
  compile_(file_path);
}

void BaseShader::compile_(const char *file_path) const noexcept {
  std::string shader_string = readShaderSource_(file_path);
  const char *shader_source_buffer = shader_string.c_str();

  glShaderSource(id_, 1, &shader_source_buffer, nullptr);
  glCompileShader(id_);

  checkErrors_(file_path);
}

void BaseShader::checkErrors_(const char *file_path) const {
  GLint success;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

  if (!success) {
    GLchar info_log[512];
    glGetShaderInfoLog(id_, sizeof(info_log), nullptr, info_log);
    ERROR_LOG(std::format("failed compiling shader \"{}\".", file_path));

    throw RUNTIME_ERROR;
  }
}

BaseShader::~BaseShader() noexcept { glDeleteShader(id_); }

auto BaseShader::getId() const noexcept -> const GLuint & { return id_; }

VertexShader::VertexShader(const char *file_path) noexcept
    : BaseShader(file_path, GL_VERTEX_SHADER) {}

FragmentShader::FragmentShader(const char *file_path) noexcept
    : BaseShader(file_path, GL_FRAGMENT_SHADER) {}
