#pragma once

#include <GLFW/glfw3.h>

class Input {
public:
  static void init(GLFWwindow *window);
  static void update();

  static bool isKeyDown(int key);
  static bool isKeyJustPressed(int key);

  static bool isMouseButtonDown(int button);
  static bool isMouseButtonJustPressed(int button);

  static double getMouseX();
  static double getMouseY();

  static double getMouseDeltaX();
  static double getMouseDeltaY();

  static double getScrollX();
  static double getScrollY();

private:
  static bool keys[GLFW_KEY_LAST];
  static bool justPressedKeys[GLFW_KEY_LAST];

  static bool mouseButtons[GLFW_MOUSE_BUTTON_LAST];
  static bool justPressedMouseButtons[GLFW_MOUSE_BUTTON_LAST];

  static double mouseX;
  static double mouseY;
  static double mouseDeltaX;
  static double mouseDeltaY;

  static double scrollX;
  static double scrollY;
};