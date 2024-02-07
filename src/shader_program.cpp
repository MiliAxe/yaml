#include "shader_program.hpp"
#include "globals.hpp"
#include "shader.hpp"

void ShaderProgram::checkErrors_() const {
  GLint success;
  glGetProgramiv(id_, GL_LINK_STATUS, &success);

  if (!static_cast<bool>(success)) {
    GLchar info_log[MAX_SHADER_LOG_BUF_SIZE];
    glGetProgramInfoLog(id_, MAX_SHADER_LOG_BUF_SIZE, nullptr, info_log);
    ERROR_LOG(std::format("failed linking shader program.\n"
                          "Reason: {}.\n",
                          info_log));

    throw RUNTIME_ERROR;
  }
}

ShaderProgram::ShaderProgram(const char *vertex_path,
                             const char *fragment_path) noexcept {
  VertexShader vertex_shader(vertex_path);
  FragmentShader fragment_shader(fragment_path);

  id_ = glCreateProgram();
  glAttachShader(id_, vertex_shader.getId());
  glAttachShader(id_, fragment_shader.getId());
  glLinkProgram(id_);

  checkErrors_();
}

void ShaderProgram::deActive() noexcept { glUseProgram(0); }

void ShaderProgram::activate() const noexcept { glUseProgram(id_); }

void ShaderProgram::deleteProgram() const noexcept { glDeleteProgram(id_); }

void ShaderProgram::setBool(const char *name, int32 value) const noexcept {
  glUniform1i(glGetUniformLocation(id_, name), value);
}

void ShaderProgram::setInt(const char *name, int32 value) const noexcept {
  glUniform1i(glGetUniformLocation(id_, name), value);
}

void ShaderProgram::setFloat(const char *name, f32 value) const noexcept {
  glUniform1f(glGetUniformLocation(id_, name), value);
}

void ShaderProgram::setVec2(const char *name,
                            const glm::vec2 &value) const noexcept {
  glUniform2fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

void ShaderProgram::setVec2(const char *name, f32 x_component, f32 y_component) const noexcept {
  glUniform2f(glGetUniformLocation(id_, name), x_component, y_component);
}

void ShaderProgram::setVec3(const char *name,
                            const glm::vec3 &value) const noexcept {
  glUniform3fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

void ShaderProgram::setVec3(const char *name, f32 x_component, f32 y_component,
                            f32 z_component) const noexcept {
  glUniform3f(glGetUniformLocation(id_, name), x_component, y_component, z_component);
}

void ShaderProgram::setVec4(const char *name,
                            const glm::vec4 &value) const noexcept {
  glUniform4fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

void ShaderProgram::setVec4(const char *name, f32 x_component, f32 y_component, f32 z_component,
                            f32 w_component) const noexcept {
  glUniform4f(glGetUniformLocation(id_, name), x_component, y_component, z_component, w_component);
}

void ShaderProgram::setMat2(const char *name,
                            const glm::mat2 &matrix) const noexcept {
  glUniformMatrix2fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

void ShaderProgram::setMat3(const char *name,
                            const glm::mat3 &matrix) const noexcept {
  glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

void ShaderProgram::setMat4(const char *name,
                            const glm::mat4 &matrix) const noexcept {
  glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

[[nodiscard]] auto ShaderProgram::getId() const noexcept -> const GLuint & {
  return id_;
}
