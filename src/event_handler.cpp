#include <event_handler.hpp>

#define ON_KEY_PRESS(KEY) if (glfwGetKey(window_, KEY) == GLFW_PRESS)
#define ON_KEY_RELEASE(KEY) if (glfwGetKey(window_, KEY) == GLFW_RELEASE)

#define ON_MOUSE_BUTTON_PRESS(BUTTON)                                          \
  if (glfwGetMouseButton(window_, BUTTON) == GLFW_PRESS)
#define ON_MOUSE_BUTTON_RELEASE(BUTTON)                                        \
  if (glfwGetMouseButton(window_, BUTTON) == GLFW_RELEASE)

void EventHandler::processKeyboardInput_(f32 delta_time) noexcept {
    for (const auto &[key, callback] : keyboard_callbacks_) {
        ON_KEY_PRESS(key) { callback(delta_time); }
    }
}

void EventHandler::processMouseInput_(const Cursor &offset_cursor) noexcept {
    for (const auto &[key, callback] : mouse_callbacks_) {
        ON_MOUSE_BUTTON_PRESS(key) { callback(offset_cursor); }
    }
}

void EventHandler::processInput(f32 delta_time, const Cursor &offset_cursor) noexcept {
    processKeyboardInput_(delta_time);
    processMouseInput_(offset_cursor);
}

void EventHandler::addKeyboardKey(int32 key,
                                  std::function<void(f32)> callback) noexcept {
    keyboard_callbacks_[key] = callback;
}

void EventHandler::addMouseKey(
    int32 key, std::function<void(const Cursor &)> callback) noexcept {
        mouse_callbacks_[key] = callback;
}

EventHandler::EventHandler(GLFWwindow *window) noexcept : window_(window) {}