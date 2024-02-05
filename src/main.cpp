#include "ebo.hpp"
#include "globals.hpp"
#include "shader_program.hpp"
#include "texture2d.hpp"
#include "utl.hpp"
#include "vao.hpp"
#include "vbo.hpp"
#include "vertex.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstddef>
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <vector>

glm::vec3 camera_position = {0.0f, 0.0f, 0.0f};
glm::vec3 camera_direction = {0.0f, 0.0f, -1.0f};
glm::vec3 camera_up = {0.0f, 1.0f, 0.0f};

float current_time;
float last_time;
float delta_time;

float fov = 60.0f;

float pitch = 0.0f;
float yaw = -90.0f;

float last_x = 0.0f;
float last_y = 0.0f;

bool first_mouse = true;

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

void initializeCubeVertices(std::vector<Vertex> &VBO_vertices) {
  VBO_vertices.reserve(36);
  for (uint8 i = 0; i < 36; ++i) {
    Vertex tmp_vertex;
    tmp_vertex.position = {vertices[i * 5 + 0], vertices[i * 5 + 1],
                           vertices[i * 5 + 2]};
    tmp_vertex.uv = {vertices[i * 5 + 3], vertices[i * 5 + 4]};
    VBO_vertices.push_back(tmp_vertex);
  }
}

void initializeCubeBuffers(VAO &vao, VBO &vbo) {
  std::vector<Vertex> VBO_vertices;
  initializeCubeVertices(VBO_vertices);
  vbo.setData(VBO_vertices);
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

void initializeTransforms(glm::mat4 &model, glm::mat4 &view,
                          glm::mat4 &projection) {
  model = glm::mat4(1.0f);
  view = glm::mat4(1.0f);
  projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(fov),
                                (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
                                0.1f, 100.0f);
  // projection = glm::ortho(-2.0f, 2.0f, 2.1f, -2.0f, -3.0f, 1000.0f);
}

void updateProjectionMatrix(glm::mat4 &projection) {
  projection = glm::perspective(glm::radians(fov),
                                (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
                                0.1f, 100.0f);
}

void updateModelTransform(glm::mat4 &model) {
  model = glm::mat4(1.0f);
  model = glm::translate(model,
                         glm::vec3(0.0f, 0.0f, glm::sin(glfwGetTime()) - 3.0f));
  model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 2.0f, 1.0f));
}

void updateShaderTransforms(ShaderProgram &shader, glm::mat4 &model,
                            glm::mat4 &view, glm::mat4 &projection) {
  shader.setMat4("model", model);
  shader.setMat4("view", view);
  shader.setMat4("projection", projection);
}

void updateViewTransform(glm::mat4 &view) {
  view = glm::lookAt(camera_position, camera_position + camera_direction,
                     camera_up);
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

void processCameraInput(GLFWwindow *window, float delta_time) {

  float tmp_speed = CAMERA_SPEED * delta_time;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera_position += camera_direction * tmp_speed;
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera_position -= camera_direction * tmp_speed;
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera_position +=
        glm::normalize(glm::cross(camera_direction, camera_up)) * tmp_speed;
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera_position -=
        glm::normalize(glm::cross(camera_direction, camera_up)) * tmp_speed;
  }

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double cur_x;
    double cur_y;
    glfwGetCursorPos(window, &cur_x, &cur_y);

    if (first_mouse) {
      last_x = (float)cur_x;
      last_y = (float)cur_y;

      first_mouse = false;
    }

    float xoffset = cur_x - last_x;
    float yoffset = last_y - cur_y;

    last_x = cur_x;
    last_y = cur_y;

    xoffset *= CAMERA_SENSITIVITY;
    yoffset *= CAMERA_SENSITIVITY;

    yaw += xoffset;
    pitch += yoffset;

    pitch = std::clamp(pitch, -89.9f, 89.9f);

    glm::vec3 new_camera_direction;
    new_camera_direction.x =
        glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
    new_camera_direction.y = glm::sin(glm::radians(pitch));
    new_camera_direction.z =
        glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

    camera_direction = new_camera_direction;

  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    first_mouse = true;
  }
}

void scroll_callback([[maybe_unused]] GLFWwindow *window,
                     [[maybe_unused]] double xoffset, double yoffset) {
  fov -= (float)yoffset;
  if (fov < 1.0f)
    fov = 1.0f;
  if (fov > 150.0f)
    fov = 150.0f;
}

int main() {
  stbi_set_flip_vertically_on_load(true);
  GLFWwindow *window = fn::initGLFWandGLAD();

  glfwSetScrollCallback(window, scroll_callback);

  ShaderProgram basic_shader("assets/shaders/basic_shaders/vert.glsl",
                             "assets/shaders/basic_shaders/frag.glsl");

  VAO vao;
  VBO vbo;
  initializeCubeBuffers(vao, vbo);

  Texture2D text0, text1;
  initializeCubeTextures(text0, text1);

  bindTexturesToShader(basic_shader, text0, text1);

  initializeOpenGLParams();

  glm::mat4 model, view, projection;
  initializeTransforms(model, view, projection);

  glClearColor(0, 0, 0, 0);
  while (!glfwWindowShouldClose(window)) {
    current_time = (float)glfwGetTime();
    delta_time = current_time - last_time;
    last_time = current_time;

    processCameraInput(window, delta_time);

    updateProjectionMatrix(projection);

    updateModelTransform(model);

    updateViewTransform(view);

    updateShaderTransforms(basic_shader, model, view, projection);

    render(window, basic_shader, vao);
  }

  basic_shader.deleteProgram();

  return EXIT_SUCCESS;
}
