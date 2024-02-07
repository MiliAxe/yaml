#include "camera.hpp"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

void FreeRoamCamera::CameraTransform::updateDirection_() noexcept {
  glm::vec3 new_direction;
  new_direction.x =
      glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
  new_direction.y = glm::sin(glm::radians(pitch_));
  new_direction.z =
      glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));

  direction_ = glm::normalize(new_direction);
}

auto FreeRoamCamera::CameraTransform::getView_() -> glm::mat4{
  return glm::lookAt(position_, position_ + direction_, up_);
}

void FreeRoamCamera::CameraTransform::updateYawPitch(const Cursor &offset) {
  pitch_ += offset.reverse().y * CAM_SENSITIVITY;
  pitch_ = std::clamp(pitch_, MIN_PITCH_DEGREE, MAX_PITCH_DEGREE);
  yaw_ += offset.x * CAM_SENSITIVITY;
}

void FreeRoamCamera::updateMatrix_() noexcept {
  glm::mat4 projection = glm::perspective(glm::radians(fov_), aspect_ratio_,
                                          NEAR_PLANE, FAR_PLANE);

  matrix_ = projection * transform.getView_();
}

FreeRoamCamera::FreeRoamCamera() noexcept {}

void FreeRoamCamera::update() noexcept {
  transform.updateDirection_();
  updateMatrix_();
}

auto FreeRoamCamera::getMatrix() -> glm::mat4 {
  return matrix_;
}

void FreeRoamCamera::setApsectRatio(float aspect_ratio) noexcept {
  aspect_ratio_ = aspect_ratio;
}

void FreeRoamCamera::CameraTransform::setNormalSpeed() noexcept {
  speed_ = INITIAL_CAM_SPEED;
}

void FreeRoamCamera::CameraTransform::setFastSpeed() noexcept {
  speed_ = INITIAL_CAM_SPEED * SPEED_GAIN_COEFFICIENT;
}

auto FreeRoamCamera::CameraTransform::getDeltaSpeed_(float delta_time)  const noexcept -> float {
  return delta_time * speed_;
}

void FreeRoamCamera::CameraTransform::moveForward(float delta_time) noexcept {
  float delta_speed = getDeltaSpeed_(delta_time);
  position_ += delta_speed * direction_;
}

void FreeRoamCamera::CameraTransform::moveBackward(float delta_time) noexcept {
  float delta_speed = getDeltaSpeed_(delta_time);
  position_ -= delta_speed * direction_;
}

void FreeRoamCamera::CameraTransform::moveLeft(float delta_time) noexcept {
  float delta_speed = getDeltaSpeed_(delta_time);
  position_ -= delta_speed * glm::normalize(glm::cross(direction_, up_));
}

void FreeRoamCamera::CameraTransform::moveRight(float delta_time) noexcept {
  float delta_speed = getDeltaSpeed_(delta_time);
  position_ += delta_speed * glm::normalize(glm::cross(direction_, up_));
}
