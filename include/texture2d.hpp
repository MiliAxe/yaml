/*
 * @file texture2d.hpp
 *
 * @brief This file contains the class declaration for texture2d class
 */

#pragma once

#include "globals.hpp"

#include <glad/glad.h>

class Texture2D {
private:
  GLuint id_;
  uint8 current_slot_ = 0;

  [[nodiscard("Image data unhandled")]] static auto
  getImageBinary(const char *image_path, int *width, int *height, int *n_channels) -> GLubyte *;
  void initTexture(GLenum wrap_s = GL_REPEAT, GLenum wrap_t = GL_REPEAT,
                          GLenum min_filter = GL_LINEAR_MIPMAP_LINEAR,
                          GLenum mag_filter = GL_LINEAR) noexcept;

  constexpr static GLenum kTexture_type = GL_TEXTURE_2D;

public:
  Texture2D();

  static void activateSlot(uint8 slot) noexcept;
  static void unbind() noexcept;
  
  void generateMipmap() const noexcept;
  void bind() const noexcept;
  void bind(uint8 slot) const noexcept;
  void deleteTexture() const noexcept;
  void loadFromFile(const char *image_path) const;
  auto getID() const noexcept -> const GLuint &;
};
