#pragma once

#include "Input.h"

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OrbitCamera {
public:
  float yaw = 45.0f;
  float pitch = 30.0f;
  float radius = 6.0f;

  float sensitivity = 0.25f;
  float scrollSensitivity = 0.5f;

  glm::vec3 target = glm::vec3(0.0f);

  void update() {
    if (Input::isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
      yaw -= Input::getMouseDeltaX() * sensitivity;
      pitch -= Input::getMouseDeltaY() * sensitivity;

      pitch = std::clamp(pitch, -89.0f, 89.0f);
    }

    radius = std::max(1.0f, radius - (float) Input::getScrollY() * scrollSensitivity);
  }

  glm::mat4 getViewMatrix() const {
    float radYaw = glm::radians(yaw);
    float radPitch = glm::radians(pitch);

    glm::vec3 position;
    position.x = radius * cos(radPitch) * cos(radYaw);
    position.y = radius * sin(radPitch);
    position.z = radius * cos(radPitch) * sin(radYaw);

    return glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
  }

  glm::vec3 getPosition() const {
    float radYaw = glm::radians(yaw);
    float radPitch = glm::radians(pitch);

    glm::vec3 position;
    position.x = radius * cos(radPitch) * cos(radYaw);
    position.y = radius * sin(radPitch);
    position.z = radius * cos(radPitch) * sin(radYaw);

    return position;
  }
};