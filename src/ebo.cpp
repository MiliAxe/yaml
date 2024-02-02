#include "ebo.hpp"

#include <vector>

EBO::EBO() noexcept { glGenBuffers(1, &id_); }

void EBO::bind() const noexcept { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }

void EBO::unbind() noexcept { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::deleteBuffer() const noexcept { glDeleteBuffers(1, &id_); }

void EBO::setData(const std::vector<GLuint> &indices) const noexcept {
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);
  unbind();
}
