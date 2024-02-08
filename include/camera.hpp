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

class BaseCamera {
protected:
  f32 fov_ = INITIAL_CAM_FOV;
  f32 aspect_ratio_ = WINDOW_WIDTH / static_cast<f32>(WINDOW_HEIGHT);
  glm::mat4 matrix_ = glm::mat4(1.0f);

  glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);

  virtual auto getView_() -> glm::mat4 = 0;
  void updateMatrix_() noexcept;

public:
  void setApsectRatio(f32 aspect_ratio) noexcept;
  [[nodiscard("value not handled.")]] auto getMatrix() const noexcept
      -> const glm::mat4 &;

  virtual void update() = 0;
  virtual void processInput(GLFWwindow *window, const Cursor &cursor_offset,
                            f32 delta_time) = 0;
};

class OrbitalCamera : public BaseCamera {
private:
  f32 z_axis_degree_ = 0.0f;
  f32 x_axis_degree_ = 0.0f;
  f32 radius_ = 5.0f;
  glm::vec3 current_position_ = glm::vec3(0.0f, 0.0f, 0.0f);
  

  virtual auto getView_() -> glm::mat4 override;
  void processMouseInput_(const Cursor &offset_cursor) noexcept;
  void setRadius_(f32 new_radius);
  auto calculateCurrentPosition_() -> glm::vec3;

public:
  OrbitalCamera() noexcept;
  virtual void processInput(GLFWwindow *window, const Cursor &cursor_offset,
                            f32 delta_time) noexcept override;
  virtual void update() override;

};

class FreeRoamCamera : public BaseCamera {
private:
  float pitch_ = 0.0f;
  float yaw_ = -90.0f;
  float speed_ = INITIAL_CAM_SPEED;

  glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, -1.0f);

  virtual auto getView_() -> glm::mat4 override;

  void processKeyboardInput_(GLFWwindow *window, f32 delta_time) noexcept;
  void processMouseInput_(const Cursor &offset_cursor) noexcept;
  void updateDirection_() noexcept;
  auto getDeltaSpeed_(f32 delta_time) const noexcept -> f32;
  void setNormalSpeed_() noexcept;
  void setFastSpeed_() noexcept;

public:
  FreeRoamCamera() noexcept;

  virtual void update() noexcept override;
  virtual void processInput(GLFWwindow *window, const Cursor &cursor_offset,
                            f32 delta_time) noexcept override;
  void updateYawPitch(const Cursor &offset);

  void moveForward(f32 delta_time) noexcept;
  void moveBackward(f32 delta_time) noexcept;
  void moveLeft(f32 delta_time) noexcept;
  void moveRight(f32 delta_time) noexcept;
};
