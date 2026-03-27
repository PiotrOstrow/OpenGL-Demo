#include "glad/glad.h"

#include "Input.h"
#include "OrbitCamera.h"
#include "Util.h"
#include "tiny_obj_loader.h"

#include "GLFW/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cstdio>

int main() {
  if (!glfwInit()) {
    printf("Failed to initialize glfw\n");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(1280, 720, "OpenGL Demo", NULL, NULL);
  if (!window) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    printf("Could not initialize GLAD\n");
    glfwTerminate();
    return -1;
  }

  // Disable v-sync
  //glfwSwapInterval(0);

  Input::init(window);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    

    glfwSwapBuffers(window);

    Input::update();
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
