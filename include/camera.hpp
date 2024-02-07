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
      void updateDirection_() noexcept;
      void updateYawPitch(const Cursor &offset);
      auto getView() -> glm::mat4;
      void moveForward(float delta_time) noexcept;
      void moveBackward(float delta_time) noexcept;
      void moveLeft(float delta_time) noexcept;
      void moveRight(float delta_time) noexcept;
      void setNormalSpeed() noexcept;
      void setFastSpeed() noexcept;

    private:
      auto getDeltaSpeed(float delta_time)  const noexcept -> float;
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


public:
  CameraTransform transform;
  FreeRoamCamera() noexcept;

  void updateMatrix_() noexcept;
  void update() noexcept;
  void setApsectRatio(float aspect_ratio) noexcept;
  void setFirstMove(bool value) noexcept;
};
