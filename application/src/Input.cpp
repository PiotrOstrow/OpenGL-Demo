#include "Input.h"
#include <cstring>

bool Input::keys[GLFW_KEY_LAST] = {};
bool Input::justPressedKeys[GLFW_KEY_LAST] = {};

bool Input::mouseButtons[GLFW_MOUSE_BUTTON_LAST] = {};
bool Input::justPressedMouseButtons[GLFW_MOUSE_BUTTON_LAST] = {};

double Input::mouseX = 0.0;
double Input::mouseY = 0.0;
double Input::mouseDeltaX = 0.0;
double Input::mouseDeltaY = 0.0;

double Input::scrollX = 0.0;
double Input::scrollY = 0.0;

void Input::init(GLFWwindow *window) {
  glfwSetKeyCallback(window, [](GLFWwindow *, int key, int, int action, int) {
    if (key >= 0 && key < GLFW_KEY_LAST) {
      keys[key] = action != GLFW_RELEASE;
      justPressedKeys[key] = action == GLFW_PRESS;
    }
  });

  glfwSetMouseButtonCallback(window, [](GLFWwindow *, int button, int action, int) {
    if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
      mouseButtons[button] = action != GLFW_RELEASE;
      justPressedMouseButtons[button] = action == GLFW_PRESS;
    }
  });

  glfwSetCursorPosCallback(window, [](GLFWwindow *, double xpos, double ypos) {
    mouseDeltaX = xpos - mouseX;
    mouseDeltaY = ypos - mouseY;
    mouseX = xpos;
    mouseY = ypos;
  });

  glfwSetScrollCallback(window, [](GLFWwindow *, double xoffset, double yoffset) {
    scrollX = xoffset;
    scrollY = yoffset;
  });
}

void Input::update() {
  memset(justPressedKeys, 0, sizeof(justPressedKeys));
  memset(justPressedMouseButtons, 0, sizeof(justPressedMouseButtons));

  mouseDeltaX = 0.0;
  mouseDeltaY = 0.0;

  scrollX = 0.0;
  scrollY = 0.0;
}

bool Input::isKeyDown(int key) {
  return keys[key];
}

bool Input::isKeyJustPressed(int key) {
  return justPressedKeys[key];
}

bool Input::isMouseButtonDown(int button) {
  return mouseButtons[button];
}

bool Input::isMouseButtonJustPressed(int button) {
  return justPressedMouseButtons[button];
}

double Input::getMouseX() {
  return mouseX;
}

double Input::getMouseY() {
  return mouseY;
}

double Input::getMouseDeltaX() {
  return mouseDeltaX;
}

double Input::getMouseDeltaY() {
  return mouseDeltaY;
}

double Input::getScrollX() {
  return scrollX;
}

double Input::getScrollY() {
  return scrollY;
}