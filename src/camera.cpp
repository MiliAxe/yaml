#include "camera.hpp"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

void FreeRoamCamera::updateDirVec_() noexcept {
  glm::vec3 new_direction;
  new_direction.x =
      glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
  new_direction.y = glm::sin(glm::radians(pitch_));
  new_direction.z =
      glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));

  direction_ = glm::normalize(new_direction);
}

void FreeRoamCamera::updateYawAndPitch(double x, double y) {
  if (first_click_move_) {
    last_cursor_x_ = static_cast<float>(x);
    last_cursor_y_ = static_cast<float>(y);
    first_click_move_ = false;
  }
  yaw_ += (x - last_cursor_x_) * CAM_SENSITIVITY;
  pitch_ += (last_cursor_y_ - y) * CAM_SENSITIVITY;
  pitch_ = std::clamp(pitch_, MIN_PITCH_DEGREE, MAX_PITCH_DEGREE);

  last_cursor_x_ = x;
  last_cursor_y_ = y;
}

// void FreeRoamCamera::processMouse_(GLFWwindow *window) noexcept {
//   if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//     double cur_x;
//     double cur_y;
//     glfwGetCursorPos(window, &cur_x, &cur_y);
//
//   } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
//              GLFW_RELEASE) {
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//     first_click_move_ = true;
//   }
// }

// void FreeRoamCamera::processKeyboard_(GLFWwindow *window,
//                                       float delta_time) noexcept {
//   float delta_speed = speed_ * delta_time;
//   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//     position_ += delta_speed * direction_;
//   }
//   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//     position_ -= delta_speed * direction_;
//   }
//   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//     position_ += delta_speed * glm::normalize(glm::cross(direction_, up_));
//   }
//   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//     position_ -= delta_speed * glm::normalize(glm::cross(direction_, up_));
//   }
//   if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
//     speed_ = INITIAL_CAM_SPEED * 3.0f;
//   }
//   if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
//     speed_ = INITIAL_CAM_SPEED;
//   }
// }

void FreeRoamCamera::updateMatrix_() noexcept {
  glm::mat4 projection = glm::perspective(glm::radians(fov_), aspect_ratio_,
                                          near_plane_, far_plane_);

  glm::mat4 view = glm::lookAt(position_, position_ + direction_, up_);

  matrix_ = projection * view;
}

FreeRoamCamera::FreeRoamCamera() noexcept {}

void FreeRoamCamera::update() noexcept {
  updateDirVec_();
  updateMatrix_();
}

void FreeRoamCamera::setApsectRatio(float aspect_ratio) noexcept {
  aspect_ratio_ = aspect_ratio;
}

void FreeRoamCamera::setPosition(const glm::vec3 &position) noexcept {
  position_ = position;
}

void FreeRoamCamera::setSpeed(float speed) noexcept { speed_ = speed; }

void FreeRoamCamera::setFirstMove(bool value) noexcept {
  first_click_move_ = value;
}

// void FreeRoamCamera::setDirection(const glm::vec3 &direction) noexcept {
//   direction_
// }

auto FreeRoamCamera::getMatrix() const noexcept -> const glm::mat4 & {
  return matrix_;
}

auto FreeRoamCamera::getPosition() const noexcept -> const glm::vec3 & {
  return position_;
}

auto FreeRoamCamera::getSpeed() const noexcept -> const float & {
  return speed_;
}

auto FreeRoamCamera::getDirection() const noexcept -> const glm::vec3 & {
  return direction_;
}

auto FreeRoamCamera::getUp() const noexcept -> const glm::vec3 & { return up_; }
