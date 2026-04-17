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

  glDisable(GL_CULL_FACE);

  struct Vertex {
    glm::vec2 position;
    glm::vec3 color;
  };

  std::vector<Vertex> vertices{};
  vertices.resize(3);

  vertices[0].position = {-.5f, -.5f};
  vertices[1].position = {0.0f, .5f};
  vertices[2].position = {.5f, -.5f};

  vertices[0].color = {1.0, 0.0, 0.0};
  vertices[1].color = {0.0, 1.0, 0.0};
  vertices[2].color = {0.0, 0.0, 1.0};

  GLuint vertexArrayObject;
  glGenVertexArrays(1, &vertexArrayObject);
  glBindVertexArray(vertexArrayObject);

  GLuint vertexBufferObject;
  glGenBuffers(1, &vertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(Vertex),
               vertices.data(),
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex),
                        (void *) offsetof(Vertex, position));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex),
                        (void *) offsetof(Vertex, color));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GLuint shaderProgram = createShaderProgram("shaders/basic.vert",
                                             "shaders/basic.frag");

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    auto location = glGetUniformLocation(shaderProgram, "u_time");
    glUniform1f(location, glfwGetTime());

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);

    Input::update();
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
