#include "camera.hpp"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

void FreeRoamCamera::processMouse_(GLFWwindow *window) noexcept {
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double cur_x;
    double cur_y;
    glfwGetCursorPos(window, &cur_x, &cur_y);

    if (first_click_move_) {
      last_cursor_x_ = static_cast<float>(cur_x);
      last_cursor_y_ = static_cast<float>(cur_y);
      first_click_move_ = false;
    }

    float x_offset = cur_x - last_cursor_x_;
    float y_offset = last_cursor_y_ - cur_y;

    last_cursor_x_ = cur_x;
    last_cursor_y_ = cur_y;

    x_offset *= CAM_SENSITIVITY;
    y_offset *= CAM_SENSITIVITY;

    yaw_ += x_offset;
    pitch_ += y_offset;

    pitch_ = std::clamp(pitch_, -89.999999f, 89.999999f);

    glm::vec3 new_direction;
    new_direction.x =
        glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
    new_direction.y = glm::sin(glm::radians(pitch_));
    new_direction.z =
        glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));

    direction_ = glm::normalize(new_direction);

  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    first_click_move_ = true;
  }
}

void FreeRoamCamera::processKeyboard_(GLFWwindow *window,
                                      float delta_time) noexcept {
  float delta_speed = speed_ * delta_time;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    position_ += delta_speed * direction_;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    position_ -= delta_speed * direction_;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    position_ += delta_speed * glm::normalize(glm::cross(direction_, up_));
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    position_ -= delta_speed * glm::normalize(glm::cross(direction_, up_));
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speed_ = INITIAL_CAM_SPEED * 3.0f;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    speed_ = INITIAL_CAM_SPEED;
  }
}

void FreeRoamCamera::updateMatrix_() noexcept {
  glm::mat4 projection = glm::perspective(glm::radians(fov_), aspect_ratio_,
                                          near_plane_, far_plane_);

  glm::mat4 view = glm::lookAt(position_, position_ + direction_, up_);

  matrix_ = projection * view;
}

FreeRoamCamera::FreeRoamCamera() noexcept {}

void FreeRoamCamera::update(GLFWwindow *window, float delta_time) noexcept {
  processKeyboard_(window, delta_time);
  processMouse_(window);
  updateMatrix_();
}

void FreeRoamCamera::setApsectRatio(float aspect_ratio) noexcept {
  aspect_ratio_ = aspect_ratio;
}

auto FreeRoamCamera::getMatrix() const noexcept -> const glm::mat4 & {
  return matrix_;
}

auto FreeRoamCamera::getPosition() const noexcept -> const glm::vec3 & {
  return position_;
}
