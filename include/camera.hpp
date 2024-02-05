/*
 *  @file camera.hpp
 *
 *  @brief Camera functionality for the model viewer.
 *
 */

#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

// TODO: remember changing aspect ratio on GLFW window resize.
class FreeRoamCamera {
private:
  float fov_ = INITIAL_CAM_FOV;
  float aspect_ratio_ = WINDOW_WIDTH / static_cast<float>(WINDOW_HEIGHT);
  float near_plane_ = 0.1f;
  float far_plane_ = 50.0f;

  float speed_ = INITIAL_CAM_SPEED;

  bool first_click_move_ = true;

  float last_cursor_x_ = 0.0f;
  float last_cursor_y_ = 0.0f;

  float pitch_ = 0.0f;
  float yaw_ = -90.0f;

  glm::vec3 up_ = {0.0f, 1.0f, 0.0f};
  glm::vec3 position_ = {0.0f, 0.0f, 3.0f};
  glm::vec3 direction_ = {0.0f, 0.0f, -1.0f};

  glm::mat4 matrix_ = glm::mat4(1.0f);

  void processMouse_(GLFWwindow *window) const noexcept;
  void processKeyboard_(GLFWwindow *window) const noexcept;
  void updateMatrix_() const noexcept;

public:
  FreeRoamCamera() noexcept;

  void update(GLFWwindow *window) const noexcept;

  void setApsectRatio(float aspect_ratio) noexcept;

  [[nodiscard("value not handled.")]] auto getMatrix() const noexcept
      -> const glm::mat4 &;
  [[nodiscard("value not handled.")]] auto getPosition() const noexcept
      -> const glm::vec3 &;
};
