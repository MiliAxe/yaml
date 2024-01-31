#include <ebo.hpp>
#include <vector>

EBO::EBO() { glGenBuffers(1, &id_); }

void EBO::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_); }

void EBO::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::deleteBuffer() { glDeleteBuffers(1, &id_); }

void EBO::setData(const std::vector<GLuint> &indices) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);
}
