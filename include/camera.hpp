/*
 *  @file camera.hpp
 *
 *  @brief Camera functionality for the model viewer.
 *
 */
#pragma once

#include "cursor.hpp"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

// TODO: remember changing aspect ratio on GLFW window resize.
// TODO: move the cursor to another class.
// TODO: leave input handeling to Apllication class and delete from here.
class FreeRoamCamera {
  class CameraTransform {

    friend class FreeRoamCamera;

  private:
    float pitch_ = 0.0f;
    float yaw_ = -90.0f;
    float speed_ = INITIAL_CAM_SPEED;

    glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, -1.0f);

    auto getView_() -> glm::mat4;
    void updateDirection_() noexcept;
    auto getDeltaSpeed_(f32 delta_time) const noexcept -> f32;

  public:
    CameraTransform() = default;
    void updateYawPitch(const Cursor &offset);
    void moveForward(f32 delta_time) noexcept;
    void moveBackward(f32 delta_time) noexcept;
    void moveLeft(f32 delta_time) noexcept;
    void moveRight(f32 delta_time) noexcept;
    void setNormalSpeed() noexcept;
    void setFastSpeed() noexcept;
  };

private:
  f32 fov_ = INITIAL_CAM_FOV;
  f32 aspect_ratio_ = WINDOW_WIDTH / static_cast<f32>(WINDOW_HEIGHT);
  glm::mat4 matrix_ = glm::mat4(1.0f);

  void updateMatrix_() noexcept;

public:
  CameraTransform transform;

  FreeRoamCamera() noexcept;

  void update() noexcept;
  void setApsectRatio(f32 aspect_ratio) noexcept;
  void setFirstMove(bool value) noexcept;

  [[nodiscard("value not handled.")]] auto getMatrix() const noexcept
      -> const glm::mat4 &;
};
