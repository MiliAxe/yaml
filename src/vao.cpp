#include "vao.hpp"
#include "vbo.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &id_);
}

void VAO::bind()
{
    glBindVertexArray(id_);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::deleteArray()
{
    glDeleteVertexArrays(1, &id_);
}

void VAO::linkVBO(const VBO &vbo, uint8 slot, uint8 n_components, GLenum type, uint8 stride, uint8 offset)
{
    bind();
    vbo.bind();

    glVertexAttribPointer(slot, n_components, type, GL_FALSE, stride, reinterpret_cast<void *>(offset));

    glEnableVertexAttribArray(slot);

    vbo.unbind();
    unbind();
}
