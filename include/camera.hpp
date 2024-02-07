/*
 *  @file camera.hpp
 *
 *  @brief Camera functionality for the model viewer.
 *
 */
#pragma once

#include "globals.hpp"
#include "cursor.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

// TODO: remember changing aspect ratio on GLFW window resize.
// TODO: move the cursor to another class.
// TODO: leave input handeling to Apllication class and delete from here.
class FreeRoamCamera {
  class CameraTransform {
    public:
      CameraTransform() = default;
      void updateYawPitch(const Cursor &offset);
      void moveForward(float delta_time) noexcept;
      void moveBackward(float delta_time) noexcept;
      void moveLeft(float delta_time) noexcept;
      void moveRight(float delta_time) noexcept;
      void setNormalSpeed() noexcept;
      void setFastSpeed() noexcept;

    private:
      auto getView_() -> glm::mat4;
      void updateDirection_() noexcept;
      auto getDeltaSpeed_(float delta_time)  const noexcept -> float;
      float pitch_ = 0.0f;
      float yaw_ = -90.0f;
      float speed_ = INITIAL_CAM_SPEED;
      glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
      glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 3.0f);
      glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, -1.0f);

      friend class FreeRoamCamera;
  };


private:
  float fov_ = INITIAL_CAM_FOV;
  float aspect_ratio_ = WINDOW_WIDTH / static_cast<float>(WINDOW_HEIGHT);
  glm::mat4 matrix_ = glm::mat4(1.0f);
  void updateMatrix_() noexcept;


public:
  CameraTransform transform;
  FreeRoamCamera() noexcept;

  void update() noexcept;
  void setApsectRatio(float aspect_ratio) noexcept;
  void setFirstMove(bool value) noexcept;
  auto getMatrix() -> glm::mat4;
};
