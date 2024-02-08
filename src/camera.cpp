#include "camera.hpp"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

void FreeRoamCamera::updateDirection_() noexcept {
  glm::vec3 new_direction;
  new_direction.x =
      glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
  new_direction.y = glm::sin(glm::radians(pitch_));
  new_direction.z =
      glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));

  direction_ = glm::normalize(new_direction);
}

auto FreeRoamCamera::getView_() -> glm::mat4 {
  return glm::lookAt(position_, position_ + direction_, up_);
}

auto FreeRoamCamera::getDeltaSpeed_(f32 delta_time) const noexcept -> f32 {
  return delta_time * speed_;
}

void FreeRoamCamera::updateYawPitch(const Cursor &offset) {
  pitch_ += -offset.y_ * CAM_SENSITIVITY;
  pitch_ = glm::clamp(pitch_, MIN_PITCH_DEGREE, MAX_PITCH_DEGREE);
  yaw_ += offset.x_ * CAM_SENSITIVITY;
}

void FreeRoamCamera::setNormalSpeed_() noexcept { speed_ = INITIAL_CAM_SPEED; }

void FreeRoamCamera::setFastSpeed_() noexcept {
  speed_ = INITIAL_CAM_SPEED * SPEED_GAIN_COEFFICIENT;
}

void FreeRoamCamera::moveForward(f32 delta_time) noexcept {
  position_ += getDeltaSpeed_(delta_time) * direction_;
}

void FreeRoamCamera::moveBackward(f32 delta_time) noexcept {
  position_ -= getDeltaSpeed_(delta_time) * direction_;
}

void FreeRoamCamera::moveLeft(f32 delta_time) noexcept {
  position_ -=
      getDeltaSpeed_(delta_time) * glm::normalize(glm::cross(direction_, up_));
}

void FreeRoamCamera::moveRight(f32 delta_time) noexcept {
  position_ +=
      getDeltaSpeed_(delta_time) * glm::normalize(glm::cross(direction_, up_));
}

void BaseCamera::updateMatrix_() noexcept {
  glm::mat4 projection = glm::perspective(glm::radians(fov_), aspect_ratio_,
                                          NEAR_PLANE, FAR_PLANE);

  matrix_ = projection * getView_();
}

#define ON_KEY_PRESS(KEY) if (glfwGetKey(window, KEY) == GLFW_PRESS)
#define ON_KEY_RELEASE(KEY) if (glfwGetKey(window, KEY) == GLFW_RELEASE)

void FreeRoamCamera::processKeyboardInput_(GLFWwindow *window,
                                           f32 delta_time) noexcept {
  ON_KEY_PRESS(GLFW_KEY_W) moveForward(delta_time);
  ON_KEY_PRESS(GLFW_KEY_S) moveBackward(delta_time);
  ON_KEY_PRESS(GLFW_KEY_D) moveRight(delta_time);
  ON_KEY_PRESS(GLFW_KEY_A) moveLeft(delta_time);
  ON_KEY_PRESS(GLFW_KEY_LEFT_SHIFT) setFastSpeed_();
  ON_KEY_RELEASE(GLFW_KEY_LEFT_SHIFT) setNormalSpeed_();
}

#define ON_MOUSE_BUTTON_PRESS(BUTTON)                                          \
  if (glfwGetMouseButton(window_, BUTTON) == GLFW_PRESS)
#define ON_MOUSE_BUTTON_RELEASE(BUTTON)                                        \
  if (glfwGetMouseButton(window_, BUTTON) == GLFW_RELEASE)

void FreeRoamCamera::processMouseInput_(const Cursor &offset_cursor) noexcept {
  updateYawPitch(offset_cursor);
}

FreeRoamCamera::FreeRoamCamera() noexcept {}

void FreeRoamCamera::update() noexcept {
  updateDirection_();
  updateMatrix_();
}

void BaseCamera::setApsectRatio(f32 aspect_ratio) noexcept {
  aspect_ratio_ = aspect_ratio;
}

void FreeRoamCamera::processInput(GLFWwindow *window,
                                  const Cursor &cursor_offset,
                                  f32 delta_time) noexcept {
  processKeyboardInput_(window, delta_time);
  processMouseInput_(cursor_offset);
}

auto BaseCamera::getMatrix() const noexcept -> const glm::mat4 & {
  return matrix_;
}

OrbitalCamera::OrbitalCamera() noexcept { position_ = {0.0f, 0.0f, radius_}; }

auto OrbitalCamera::getView_() -> glm::mat4 {
  glm::vec3 target(0.0f, 0.0f, 0.0f);
  return glm::lookAt(position_, target, up_);
}

void OrbitalCamera::processMouseInput_(const Cursor &offset_cursor) noexcept {
  y_axis_degree_ += offset_cursor.y_;
  y_axis_degree_ = std::clamp(y_axis_degree_, -89.0f, 89.0f);
  x_axis_degree_ -= offset_cursor.x_;
}

void OrbitalCamera::setRadius_(f32 new_radius) { radius_ = new_radius; }

auto OrbitalCamera::calculateCurrentPosition_() -> glm::vec3 {
  glm::vec3 new_position;

  new_position.y = glm::sin(glm::radians(y_axis_degree_)) * radius_;

  new_position.x = glm::sin(glm::radians(x_axis_degree_)) *
                   glm::cos(glm::radians(y_axis_degree_)) * radius_;

  new_position.z = glm::cos(glm::radians(x_axis_degree_)) *
                   glm::cos(glm::radians(y_axis_degree_)) * radius_;

  return new_position;
}

void OrbitalCamera::processInput([[maybe_unused]] GLFWwindow *window,
                                 const Cursor &cursor_offset,
                                 [[maybe_unused]] f32 delta_time) noexcept {
  processMouseInput_(cursor_offset);
  position_ = calculateCurrentPosition_();
}

void OrbitalCamera::update() { updateMatrix_(); }
