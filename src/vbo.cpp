#include <vbo.hpp>

VBO::VBO() { glGenBuffers(1, &id_); }

void VBO::bind() { glBindBuffer(GL_ARRAY_BUFFER, id_); }

void VBO::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::setData(const std::vector<Vertex> &data) {
  bind();
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(),
               GL_STATIC_DRAW);
  unbind();
};
