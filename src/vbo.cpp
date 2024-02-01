#include "vbo.hpp"

VBO::VBO() noexcept { glGenBuffers(1, &id_); }

void VBO::bind() const noexcept { glBindBuffer(GL_ARRAY_BUFFER, id_); }

void VBO::unbind() noexcept { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::deleteBuffer() const noexcept { glDeleteBuffers(1, &id_); }

void VBO::setData(const std::vector<Vertex> &data) const noexcept {
  bind();
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(),
               GL_STATIC_DRAW);
  unbind();
};
