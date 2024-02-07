/*
 *  @file globals.hpp
 *
 *  @brief globals tools used in development workflow
 */

#pragma once

#include <cstdint>
#include <exception>
#include <filesystem>
#include <format>
#include <glad/glad.h>
#include <stdexcept>
#include <string_view>

#define __FILENAME__ std::filesystem::path(__FILE__).filename().string()

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using f32 = float;
using f64 = double;

[[maybe_unused]] inline static void
_loader_message_log(std::string_view msg, std::string_view file, int32 line) {
  std::puts(
      std::format("[MESSAGE] in {} at line {} - \"{}\" \n", file, line, msg)
          .c_str());
}
#define MSG_LOG(m) _loader_message_log(m, __FILENAME__, __LINE__)

[[maybe_unused]] inline static void
_loader_error_log(std::string_view msg, std::string_view file, int32 line) {
  std::puts(std::format("[ERROR] in {} at line {} - \"{}\" \n", file, line, msg)
                .c_str());
}
#define ERROR_LOG(m) _loader_error_log(m, __FILENAME__, __LINE__)

#define RUNTIME_ERROR std::runtime_error("Error detected, check log!")

#define IS_VERBOSE 1

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Develop window"
#define WINDOW_MONITOR nullptr
#define WINDOW_SHARE nullptr

#define INITIAL_CAM_FOV 66.0f
#define INITIAL_CAM_SPEED 5.0f
#define CAM_SENSITIVITY 0.1f
#define MAX_PITCH_DEGREE 89.999f
#define MIN_PITCH_DEGREE -89.999f
#define SPEED_GAIN_COEFFICIENT 3.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 50.0f
