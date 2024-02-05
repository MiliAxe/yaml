#include "camera.hpp"

void FreeRoamCamera::processMouse_(GLFWwindow *window) const noexcept {}

void FreeRoamCamera::processKeyboard_(GLFWwindow *window) const noexcept {}

void FreeRoamCamera::updateMatrix_() const noexcept {}

void FreeRoamCamera::update(GLFWwindow *window) const noexcept {}

void FreeRoamCamera::setApsectRatio(float aspect_ratio) noexcept {}

auto FreeRoamCamera::getMatrix() const noexcept -> const glm::mat4 & {}

auto FreeRoamCamera::getPosition() const noexcept -> const glm::vec3 & {}
