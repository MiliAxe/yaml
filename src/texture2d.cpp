#include "texture2d.hpp"
#include "globals.hpp"

#include <format>
#include <stb_image.h>

auto Texture2D::getImageBinary(const char *image_path, int32 *width, int32 *height,
                               int32 *n_channels) -> GLubyte * {
  GLubyte *data =
      stbi_load(image_path, width, height, n_channels, STBI_rgb_alpha);

  if (!data) {
    ERROR_LOG(std::format("Could not load image from {}\n Reason: {}",
                          image_path, stbi_failure_reason()));
    throw RUNTIME_ERROR;
  }

  return data;
}

Texture2D::Texture2D() {
  glGenTextures(1, &id_);
  initTexture();
}

void Texture2D::activateSlot(uint8 slot) noexcept {
  glActiveTexture(GL_TEXTURE0 + slot);
  current_slot_ = slot;
}

void Texture2D::initTexture(GLenum wrap_s, GLenum wrap_t, GLenum min_filter,
                            GLenum mag_filter) noexcept {
  bind();
  glTexParameteri(kTexture_type, GL_TEXTURE_WRAP_S, wrap_s);
  glTexParameteri(kTexture_type, GL_TEXTURE_WRAP_T, wrap_t);
  glTexParameteri(kTexture_type, GL_TEXTURE_MIN_FILTER, min_filter);
  glTexParameteri(kTexture_type, GL_TEXTURE_MAG_FILTER, mag_filter);
  unbind();
}

void Texture2D::unbind() noexcept {
  is_bound = false;
  glBindTexture(kTexture_type, 0);
}

void Texture2D::bind() noexcept {
  is_bound = true;
  glBindTexture(kTexture_type, id_);
}

void Texture2D::bind(uint8 slot) noexcept {
  activateSlot(slot);
  bind();
}

void Texture2D::generateMipmap() noexcept {
  bind();
  glGenerateMipmap(kTexture_type);
  unbind();
}

void Texture2D::deleteTexture() const noexcept { glDeleteTextures(1, &id_); }

void Texture2D::loadFromFile(const char *image_path) {
  int32 width, height, n_channels;
  GLubyte *data = getImageBinary(image_path, &width, &height, &n_channels);
  bind();
  glTexImage2D(kTexture_type, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  generateMipmap();
  unbind();

  stbi_image_free(data);
}

auto Texture2D::getID() const noexcept -> const GLuint & { return id_; }

auto Texture2D::getCurrentSlot() const -> const uint8 & {
  if (!is_bound) {
    ERROR_LOG("Trying to get the slot of an unbound texture");
    throw RUNTIME_ERROR;
  }
  return current_slot_;
}
