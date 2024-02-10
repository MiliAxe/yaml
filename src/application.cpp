#include "application.hpp"
#include "cube_model.hpp"
#include "globals.hpp"
#include "shader_program.hpp"
#include "texture2d.hpp"
#include "vao.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

void Application::windowSizeCallback_(GLFWwindow *window, int32 width,
                                      int32 height) noexcept {
  auto *instance =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  instance->windowResize_(width, height);
}

void Application::windowResize_(f32 width, f32 height) noexcept {
  glViewport(0, 0, width, height);
  free_cam_.setApsectRatio(width / height);
  orbit_cam_.setApsectRatio(width / height);
}

void Application::windowKeyCallback_(GLFWwindow *window, int32 key,
                                     [[maybe_unused]] int32 scan_code,
                                     int32 action,
                                     [[maybe_unused]] int32 mods) noexcept {
  auto *instance =
      reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
  instance->keyCallbacks(key, action);
}

#define ON_KEY_PRESS(KEY) if (key == KEY && action == GLFW_PRESS)
#define ON_KEY_RELEASE(KEY) if (key == KEY && action == GLFW_RELEASE)

void Application::keyCallbacks(int32 key, int32 action) noexcept {
  ON_KEY_PRESS(GLFW_KEY_ESCAPE) { glfwSetWindowShouldClose(window_, true); }

  ON_KEY_PRESS(GLFW_KEY_W) {
    currentCamera_->input_handler_.keyState(GLFW_KEY_W, true);
  }
  ON_KEY_RELEASE(GLFW_KEY_W) {
    currentCamera_->input_handler_.keyState(GLFW_KEY_W, false);
  }

  ON_KEY_PRESS(GLFW_KEY_A) {
    currentCamera_->input_handler_.keyState(GLFW_KEY_A, true);
  }
  ON_KEY_RELEASE(GLFW_KEY_A) {
    currentCamera_->input_handler_.keyState(GLFW_KEY_A, false);
  }

  ON_KEY_PRESS(GLFW_KEY_S) {
    currentCamera_->input_handler_.keyState(GLFW_KEY_S, true);
  }
  ON_KEY_RELEASE(GLFW_KEY_S) {
    currentCamera_->input_handler_.keyState(GLFW_KEY_S, false);
  }

  ON_KEY_PRESS(GLFW_KEY_D) {
    currentCamera_->input_handler_.keyState(GLFW_KEY_D, true);
  }
  ON_KEY_RELEASE(GLFW_KEY_D) {
    currentCamera_->input_handler_.keyState(GLFW_KEY_D, false);
  }
}

#define ON_MOUSE_BUTTON_PRESS(BUTTON)                                          \
  if (glfwGetMouseButton(window_, BUTTON) == GLFW_PRESS)
#define ON_MOUSE_BUTTON_RELEASE(BUTTON)                                        \
  if (glfwGetMouseButton(window_, BUTTON) == GLFW_RELEASE)
#define SET_CURSOR_MODE(MODE) glfwSetInputMode(window_, GLFW_CURSOR, MODE)

void Application::processInput_() noexcept {
  if (ImGui::GetIO().WantCaptureMouse) {
    return;
  }
  if (glfwGetKey(window_, GLFW_KEY_O) == GLFW_PRESS) {
    currentCamera_ = &orbit_cam_;
  }
  if (glfwGetKey(window_, GLFW_KEY_F) == GLFW_PRESS) {
    currentCamera_ = &free_cam_;
  }
  ON_MOUSE_BUTTON_PRESS(GLFW_MOUSE_BUTTON_LEFT) {
    SET_CURSOR_MODE(GLFW_CURSOR_DISABLED);
    auto &io = ImGui::GetIO();
    Cursor offset = {io.MouseDelta.x, io.MouseDelta.y};
    currentCamera_->input_handler_.handle_callback(offset, delta_time_);
  }
  ON_MOUSE_BUTTON_RELEASE(GLFW_MOUSE_BUTTON_LEFT) {
    SET_CURSOR_MODE(GLFW_CURSOR_NORMAL);
  }
}

void Application::init_() {
  initGLFW_();
  initGLAD_();
  setGlParams_();
}

void Application::initGLFW_() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WINDOW_GL_VERSION_MAJOR);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WINDOW_GL_VERSION_MINOR);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if (!static_cast<bool>(glfwInit())) {
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
  glfwSwapInterval(static_cast<int>(true));

  glfwSetWindowSizeCallback(window_, windowSizeCallback_);
  glfwSetKeyCallback(window_, windowKeyCallback_);
}

void Application::initGLAD_() {
  if (!static_cast<bool>(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))) {
    ERROR_LOG("Failed binding glad.");
    throw RUNTIME_ERROR;
  }
}

void Application::setGlParams_() noexcept {
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
  processInput_();
  currentCamera_->update();
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
  };

  ShaderProgram basic_shader("assets/shaders/vert.glsl",
                             "assets/shaders/frag.glsl");
  CubeModel cube;

  VAO vao;
  VBO vbo;
  initializeCubeBuffers(vao, vbo, cube);

  Texture2D text0, text1;
  // initializeCubeTextures(text0, text1);
  // bindTexturesToShader(basic_shader, text0, text1);

  glm::mat4 model(1.0f);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      window_, true); // Second param install_callback=true will install
                      // GLFW callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();

  glClearColor(0, 0, 0, 0);
  while (!static_cast<bool>(glfwWindowShouldClose(window_))) {
    basic_shader.setFloat("time", glfwGetTime());
    // updateModelTransform(model);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update_();
    updateShaderTransforms(basic_shader, model, currentCamera_->getMatrix());
    render(basic_shader, vao);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow(); // Show demo window! :)

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
