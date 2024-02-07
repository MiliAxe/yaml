#include "application.hpp"
#include "cube_model.hpp"
#include "globals.hpp"
#include "shader_program.hpp"
#include "texture2d.hpp"
#include "vao.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

void Application::windowSizeCallback_(GLFWwindow *window, int32 width,
                                      int32 height) noexcept {
  Application *instance =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  instance->windowResize_(width, height);
}

void Application::windowResize_(f32 width, f32 height) noexcept {
  glViewport(0, 0, width, height);
  camera_.setApsectRatio(width / height);
}

void Application::windowKeyCallback_(GLFWwindow *window, int32 key,
                                     [[maybe_unused]] int32 scan_code,
                                     int32 action,
                                     [[maybe_unused]] int32 mods) noexcept {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

#define ON_KEY_PRESS(KEY) if (glfwGetKey(window_, KEY) == GLFW_PRESS)
#define ON_KEY_RELEASE(KEY) if (glfwGetKey(window_, KEY) == GLFW_RELEASE)

void Application::processKeyboardInput_() noexcept {
  ON_KEY_PRESS(GLFW_KEY_W) camera_.transform.moveForward(delta_time_);
  ON_KEY_PRESS(GLFW_KEY_S) camera_.transform.moveBackward(delta_time_);
  ON_KEY_PRESS(GLFW_KEY_D) camera_.transform.moveRight(delta_time_);
  ON_KEY_PRESS(GLFW_KEY_A) camera_.transform.moveLeft(delta_time_);
  ON_KEY_PRESS(GLFW_KEY_LEFT_SHIFT) camera_.transform.setFastSpeed();
  ON_KEY_RELEASE(GLFW_KEY_LEFT_SHIFT) camera_.transform.setNormalSpeed();
}

#define SET_CURSOR_MODE(MODE) glfwSetInputMode(window, GLFW_CURSOR, MODE)

auto Application::Mouse::mousePressReturnOffset(GLFWwindow *window) -> Cursor {
  SET_CURSOR_MODE(GLFW_CURSOR_DISABLED);
  Cursor cursor = Cursor::fromWindow(window);
  if (first_click_) {
    last_cursor_ = cursor;
    first_click_ = false;
  }
  Cursor offset = cursor - last_cursor_;

  last_cursor_ = cursor;
  return offset;
}

void Application::Mouse::mouseRelease(GLFWwindow *window) {
  SET_CURSOR_MODE(GLFW_CURSOR_NORMAL);
  first_click_ = true;
}

#define ON_MOUSE_BUTTON_PRESS(BUTTON)                                          \
  if (glfwGetMouseButton(window_, BUTTON) == GLFW_PRESS)
#define ON_MOUSE_BUTTON_RELEASE(BUTTON)                                        \
  if (glfwGetMouseButton(window_, BUTTON) == GLFW_RELEASE)

void Application::processMouseInput_() noexcept {
  ON_MOUSE_BUTTON_PRESS(GLFW_MOUSE_BUTTON_LEFT) {
    auto offset = mouse.mousePressReturnOffset(window_);
    camera_.transform.updateYawPitch(offset);
  }
  ON_MOUSE_BUTTON_RELEASE(GLFW_MOUSE_BUTTON_LEFT) {
    mouse.mouseRelease(window_);
  }
}

void Application::init_() {
  initGLFW_();
  initGLAD_();
  setGlParams_();
}

void Application::initGLFW_() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if (!glfwInit()) {
    ERROR_LOG("Failed to init GLFW.");
    throw RUNTIME_ERROR;
  }

  window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,
                             WINDOW_MONITOR, WINDOW_SHARE);
  if (window_ == nullptr) {
    ERROR_LOG("GLFW window is null.");
    glfwTerminate();
    throw RUNTIME_ERROR;
  }

  glfwMakeContextCurrent(window_);
  glfwSwapInterval(true);

  glfwSetWindowSizeCallback(window_, windowSizeCallback_);
  glfwSetKeyCallback(window_, windowKeyCallback_);
}

void Application::initGLAD_() const {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    ERROR_LOG("Failed binding glad.");
    throw RUNTIME_ERROR;
  }
}

void Application::setGlParams_() const noexcept {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Application::updateDeltaTime_() noexcept {
  f32 current_time = static_cast<f32>(glfwGetTime());
  static f32 last_time;
  delta_time_ = current_time - last_time;
  last_time = current_time;
}

void Application::update_() noexcept {
  updateDeltaTime_();
  processKeyboardInput_();
  processMouseInput_();
  camera_.update();
}

Application::Application() noexcept {
  init_();
  glfwSetWindowUserPointer(window_, reinterpret_cast<void *>(this));
}

Application::~Application() noexcept { glfwTerminate(); }

void Application::run() {
  auto initializeCubeBuffers = [](const VAO &vao, const VBO &vbo,
                                  CubeModel &model) {
    vbo.setData(model.cube);
    vao.linkVBO(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
    vao.linkVBO(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
    vao.linkVBO(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, uv));
  };

  auto initializeCubeTextures = [](Texture2D &tex0, Texture2D &tex1) {
    tex0.loadFromFile("assets/textures/brandon.png");
    tex1.loadFromFile("assets/textures/brandon2.png");
  };

  auto updateModelTransform = [](glm::mat4 &model) {
    model = glm::mat4(1.0f);
    model = glm::translate(
        model, glm::vec3(0.0f, 0.0f, glm::sin(glfwGetTime()) - 3.0f));
    model =
        glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 2.0f, 1.0f));
  };

  auto updateShaderTransforms = [](const ShaderProgram &shader,
                                   const glm::mat4 &model,
                                   const glm::mat4 &camera) {
    shader.setMat4("model", model);
    shader.setMat4("camera", camera);
  };

  auto bindTexturesToShader = [](ShaderProgram &shader, Texture2D &text0,
                                 Texture2D &text1) {
    shader.activate();
    text0.bind(0);
    text1.bind(1);
    shader.setInt("tex0", text0.getCurrentSlot());
    shader.setInt("tex1", text1.getCurrentSlot());
    shader.deActive();
  };

  auto render = [&](ShaderProgram &shader, VAO &vao) noexcept {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.activate();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glfwSwapBuffers(window_);
    glfwPollEvents();
  };

  ShaderProgram basic_shader("assets/shaders/vert.glsl",
                             "assets/shaders/frag.glsl");
  CubeModel cube;

  VAO vao;
  VBO vbo;
  initializeCubeBuffers(vao, vbo, cube);

  Texture2D text0, text1;
  initializeCubeTextures(text0, text1);
  bindTexturesToShader(basic_shader, text0, text1);

  glm::mat4 model(1.0f);

  glClearColor(0, 0, 0, 0);
  while (!glfwWindowShouldClose(window_)) {
    basic_shader.setFloat("time", glfwGetTime());
    updateModelTransform(model);

    update_();

    updateShaderTransforms(basic_shader, model, camera_.getMatrix());

    render(basic_shader, vao);
  }
}
