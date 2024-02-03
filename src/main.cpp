#include "ebo.hpp"
#include "shader_program.hpp"
#include "utl.hpp"
#include "vao.hpp"
#include "vbo.hpp"
#include "vertex.hpp"
#include "texture2d.hpp"

#include <GLFW/glfw3.h>
#include <cstddef>
#include <vector>

std::vector<Vertex> vertices;

std::vector<unsigned int> indices = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

int main() {
  GLFWwindow *window = fn::initGLFWandGLAD();

  ShaderProgram basic_shader("assets/shaders/basic_shaders/vert.glsl",
                             "assets/shaders/basic_shaders/frag.glsl");

  vertices.reserve(4);
  Vertex a;
  a.position = {0.5f, 0.5f, 0.0f};
  a.color = {0.32f, 0.24f, 0.87f};
  a.uv = {1.0f, 1.0f};
  Vertex b;
  b.position = {0.5f, -0.5f, 0.0f};
  b.color = {0.25f, 0.57f, 0.17f};
  b.uv = {1.0f, 0.0f};
  Vertex c;
  c.position = {-0.5f, -0.5f, 0.0f};
  c.color = {0.32f, 0.13f, 0.40f};
  c.uv = {0.0f, 0.0f};
  Vertex d;
  d.position = {-0.5f, 0.5f, 0.0f};
  d.color = {0.17f, 0.54f, 0.97f};
  d.uv = {0.0f, 1.0f};

  vertices.push_back(a);
  vertices.push_back(b);
  vertices.push_back(c);
  vertices.push_back(d);

  VAO vao;
  VBO vbo;
  vbo.setData(vertices);
  vao.linkVBO(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
  vao.linkVBO(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
  vao.linkVBO(vbo, 2, 2, GL_FLOAT, sizeof(Vertex) , offsetof(Vertex, uv));

  EBO ebo;
  ebo.setData(indices);

  Texture2D text0;
  // text0.loadFromFile("assets/textures/brandon.png");
  

  glClearColor(0, 0, 0, 0);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    basic_shader.activate();
    // text0.bind(0);
    vao.bind();
    ebo.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  basic_shader.deleteProgram();

  return EXIT_SUCCESS;
}
