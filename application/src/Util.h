#pragma once

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "tiny_obj_loader.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

struct MeshVertex {
  glm::vec3 position;
  glm::vec3 normal;
};

struct MeshData {
  std::vector<MeshVertex> vertices;
};

inline MeshData loadModel(const char *path) {
  MeshData meshData{};

  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig reader_config;
  reader_config.mtl_search_path = "./";

  if (!reader.ParseFromFile(path, reader_config)) {
    if (!reader.Error().empty()) {
      std::cerr << reader.Error() << std::endl;
    }
    return meshData;
  }

  auto &attrib = reader.GetAttrib();
  auto &shapes = reader.GetShapes();

  const auto &shape = shapes[0];
  meshData.vertices.resize(shape.mesh.indices.size());

  for (int i = 0; i < shape.mesh.indices.size(); i++) {
    auto &vertex = meshData.vertices[i];
    const auto index = shape.mesh.indices[i];

    vertex.position.x = attrib.vertices[3 * index.vertex_index + 0];
    vertex.position.y = attrib.vertices[3 * index.vertex_index + 1];
    vertex.position.z = attrib.vertices[3 * index.vertex_index + 2];

    if (index.normal_index >= 0) {
      vertex.normal.x = attrib.normals[3 * index.normal_index + 0];
      vertex.normal.y = attrib.normals[3 * index.normal_index + 1];
      vertex.normal.z = attrib.normals[3 * index.normal_index + 2];
    } else {
      vertex.normal = {0.0f, 0.0f, 0.0f};
    }
  }

  return meshData;
}

inline std::string readFileToString(const char *path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open file: " + std::string(path));
  }

  file.seekg(0, std::ios::end);
  std::string result(file.tellg(), '\0');
  file.seekg(0, std::ios::beg);
  file.read(result.data(), result.size());

  return result;
}

inline uint64_t getTimeMs() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline GLuint compileShader(const std::string &source, GLenum type) {
  GLuint shader = glCreateShader(type);
  if (shader == 0) {
    std::cerr << "ERROR: Failed to create shader" << std::endl;
    return 0;
  }

  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (success != GL_TRUE) {
    GLint logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

    std::string log(logLength, '\0');
    glGetShaderInfoLog(shader, logLength, nullptr, log.data());

    std::cerr << "SHADER COMPILATION ERROR:" << std::endl
              << log << std::endl;

    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

inline GLuint createShaderProgram(const char *vertexShaderPath,
                                  const char *fragmentShaderPath) {

  std::string vertexSource = readFileToString(vertexShaderPath);
  std::string fragmentSource = readFileToString(fragmentShaderPath);

  GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
  GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

  if (!vertexShader || !fragmentShader) {
    std::cerr << "ERROR: Shader compilation failed" << std::endl;
    return 0;
  }

  GLuint program = glCreateProgram();
  if (program == 0) {
    std::cerr << "ERROR: Failed to create shader program" << std::endl;
    return 0;
  }

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (success != GL_TRUE) {
    GLint logLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

    std::string log(logLength, '\0');
    glGetProgramInfoLog(program, logLength, nullptr, log.data());

    std::cerr << "PROGRAM LINKING ERROR:" << std::endl
              << log << std::endl;

    glDeleteProgram(program);
    program = 0;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}