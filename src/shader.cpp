#include "shader.hpp"
#include "globals.hpp"

#include <fstream>
#include <ios>
#include <sys/types.h>

auto Shader::readShaderSource_(const char *file_path) noexcept -> char * {
  char *buffer;

  std::ifstream file(file_path, std::ios::binary);
  std::string buffer_string;

  if (file.good()) {
    buffer_string = std::string(std::istreambuf_iterator<char>(file),
                                std::istreambuf_iterator<char>());
  }

  buffer = new char[buffer_string.size()];
  for (uint64 i = 0; i < buffer_string.size(); ++i) {
    buffer[i] = buffer_string[i];
  }

  return buffer;
}

void Shader::create_(GLenum type, const char *file_path) const noexcept {
  GLuint shader = glCreateShader(type);
  const char *shader_source = readShaderSource_(file_path);

  glShaderSource(shader, 1, &shader_source, nullptr);
  glCompileShader(shader);
  if (!checkErrors_()) {
    ERROR_LOG("shader created with success.");
  }

  delete[] shader_source;
}

auto Shader::checkErrors_() const noexcept -> bool {
  GLint success;
  GLchar info_log[512];

  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(id_, 512, nullptr, info_log);
    ERROR_LOG(std::format("failed to compile shader of type {}.\n"
                          "File : {}.\n"
                          "Info : {}.\n",
                          type_name_, file_path_, info_log));
    return false;
  }

  return true;
}

Shader::Shader(GLenum type, const char *file_path)
    : type_(type), file_path_(file_path) {
  switch (type) {
  case GL_VERTEX_SHADER:
    type_name_ = "vertex";
    break;
  case GL_FRAGMENT_SHADER:
    type_name_ = "fragment";
    break;
  default:
    type_name_ = "unknown";
    break;
  }

  create_(type, file_path);
}

Shader::~Shader() { glDeleteShader(id_); }

void Shader::deleteShader() const noexcept { glDeleteProgram(id_); }

auto Shader::getId() const noexcept -> const GLuint & { return id_; }
