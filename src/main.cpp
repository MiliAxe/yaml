#include "application.hpp"
#include "camera.hpp"
#include "cube_model.hpp"
#include "globals.hpp"
#include "shader_program.hpp"
#include "texture2d.hpp"
#include "utl.hpp"
#include "vao.hpp"
#include "vbo.hpp"
#include "vertex.hpp"

#include <GLFW/glfw3.h>
#include <cstddef>
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

void initializeCubeBuffers(VAO &vao, VBO &vbo, CubeModel &model) {
  vbo.setData(model.cube);
  vao.linkVBO(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
  vao.linkVBO(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
  vao.linkVBO(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, uv));
}

void initializeCubeTextures(Texture2D &text0, Texture2D &text1) {
  text0.loadFromFile("assets/textures/brandon.png");
  text1.loadFromFile("assets/textures/arch.png");
}

void initializeOpenGLParams() {
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initializeTransforms(glm::mat4 &model) { model = glm::mat4(1.0f); }

void updateModelTransform(glm::mat4 &model) {
  model = glm::mat4(1.0f);
  model = glm::translate(model,
                         glm::vec3(0.0f, 0.0f, glm::sin(glfwGetTime()) - 3.0f));
  model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 2.0f, 1.0f));
}

void updateShaderTransforms(const ShaderProgram &shader, const glm::mat4 &model,
                            // glm::mat4 &view, glm::mat4 &projection) {
                            const glm::mat4 &camera) {
  shader.setMat4("model", model);
  shader.setMat4("camera", camera);
}

void bindTexturesToShader(ShaderProgram &shader, Texture2D &text0,
                          Texture2D &text1) {
  shader.activate();
  text0.bind(0);
  text1.bind(1);
  shader.setInt("tex0", text0.getCurrentSlot());
  shader.setInt("tex1", text1.getCurrentSlot());
  shader.deActive();
}

void render(GLFWwindow *window, ShaderProgram &shader, VAO &vao) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.activate();
  vao.bind();
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

int main() {
  // stbi_set_flip_vertically_on_load(true);
  // GLFWwindow *window = fn::initGLFWandGLAD();
  //
  // ShaderProgram basic_shader("assets/shaders/basic_shaders/vert.glsl",
  //                            "assets/shaders/basic_shaders/frag.glsl");
  // CubeModel cube;
  //
  // VAO vao;
  // VBO vbo;
  // initializeCubeBuffers(vao, vbo, cube);
  //
  // Texture2D text0, text1;
  // initializeCubeTextures(text0, text1);
  //
  // FreeRoamCamera camera;
  //
  // initializeOpenGLParams();
  //
  // glm::mat4 model;
  // initializeTransforms(model);
  //
  // glClearColor(0, 0, 0, 0);
  // while (!glfwWindowShouldClose(window)) {
  //   updateModelTransform(model);
  //
  //   camera.update(window, delta_time);
  //
  //   updateShaderTransforms(basic_shader, model, camera.getMatrix());
  //
  //   render(window, basic_shader, vao);
  // }
  //
  // basic_shader.deleteProgram();

  Application app;
  app.init();
  app.run();

  return EXIT_SUCCESS;
}
