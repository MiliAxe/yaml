#include "shader.hpp"
#include "globals.hpp"

#include <fstream>
#include <ios>
#include <sys/types.h>

auto BaseShader::readShaderSource_(const char *file_path) -> char * {
  char *buffer;
  uint64 buffer_length;
  std::ifstream file(file_path, std::ios::binary);

  if (!file.is_open()) {
    ERROR_LOG(std::format("file \"{}\" could not be oppened.", file_path));
    throw RUNTIME_ERROR;
  }

  file.seekg(0, std::ios::end);
  buffer_length = file.tellg();
  file.seekg(0, std::ios::beg);

  buffer = new char[buffer_length];

  file.read(buffer, buffer_length);
  file.close();

  return buffer;
}

BaseShader::BaseShader(const char *file_path, GLenum type) {
  id_ = glCreateShader(type);
  compile_(file_path);
}

void BaseShader::compile_(const char *file_path) noexcept {
  const char *shader_source = readShaderSource_(file_path);

  glShaderSource(id_, 1, &shader_source, nullptr);
  glCompileShader(id_);

  checkErrors_(file_path);

  delete[] shader_source;
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

BaseShader::~BaseShader() { glDeleteShader(id_); }

VertexShader::VertexShader(const char *file_path)
    : BaseShader(file_path, GL_VERTEX_SHADER) {}

FragmentShader::FragmentShader(const char *file_path)
    : BaseShader(file_path, GL_FRAGMENT_SHADER) {}
