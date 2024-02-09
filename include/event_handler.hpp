/*
 * @file event_handler.hpp
 *
 * @brief This file contains the declaration of the EventHandler class.
 */

#pragma once

#include "globals.hpp"
#include "cursor.hpp"

#include <functional>
#include <map>

class EventHandler {
private:
    GLFWwindow *window_;
    std::map<int32, std::function<void(f32)>> keyboard_callbacks_;
    std::map<int32, std::function<void(const Cursor &)>> mouse_callbacks_;

    void processKeyboardInput_(f32 delta_time) noexcept;
    void processMouseInput_(const Cursor &offset_cursor) noexcept;

public:
    EventHandler() = default;
    EventHandler(GLFWwindow *window) noexcept;
    void addKeyboardKey(int32 key, std::function<void(f32)> callback) noexcept;
    void addMouseKey(int32 key, std::function<void(const Cursor &)> callback) noexcept;
    void processInput(f32 delta_time, const Cursor &offset_cursor) noexcept;
};