#include "shader.hpp"
#include "globals.hpp"

#include <fstream>
#include <ios>
#include <sys/types.h>

auto BaseShader::readShaderSource_(const char *file_path) noexcept -> char * {
  char *buffer;

  std::ifstream file(file_path, std::ios::binary);
  std::string buffer_string;

  if (!file.is_open()) {
    ERROR_LOG("could not open shader file.");
    return nullptr;
  }

  buffer_string = std::string(std::istreambuf_iterator<char>(file),
                              std::istreambuf_iterator<char>());

  file.close();

  buffer = new char[buffer_string.size()];
  for (uint64 i = 0; i < buffer_string.size(); ++i) {
    buffer[i] = buffer_string[i];
  }

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

  GLint success;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar info_log[512];
    glGetShaderInfoLog(id_, sizeof(info_log), nullptr, info_log);
    ERROR_LOG(std::format("failed compiling shader \"{}\".", file_path));
  }
}

BaseShader::~BaseShader() { glDeleteShader(id_); }

VertexShader::VertexShader(const char *file_path)
    : BaseShader(file_path, GL_VERTEX_SHADER) {}

FragmentShader::FragmentShader(const char *file_path)
    : BaseShader(file_path, GL_FRAGMENT_SHADER) {}
