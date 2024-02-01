#include "vao.hpp"
#include "vbo.hpp"

VAO::VAO() noexcept { glGenVertexArrays(1, &id_); }

void VAO::bind() const noexcept { glBindVertexArray(id_); }

void VAO::unbind() noexcept { glBindVertexArray(0); }

void VAO::deleteArray() const noexcept { glDeleteVertexArrays(1, &id_); }

void VAO::linkVBO(VBO &vbo, uint8 slot, uint8 n_components, GLenum type,
                  uint8 stride, uint8 offset) const noexcept {
  bind();
  vbo.bind();

  glVertexAttribPointer(slot, n_components, type, GL_FALSE, stride,
                        reinterpret_cast<void *>(offset));

  glEnableVertexAttribArray(slot);

  vbo.unbind();
  unbind();
}
