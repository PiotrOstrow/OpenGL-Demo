#version 410

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

uniform mat4 u_projection;
uniform mat4 u_view;

out vec3 v_normal;
out vec3 v_fragmentPosition;

void main() {
  gl_Position = u_projection * u_view * vec4(a_position, 1.0);
  v_fragmentPosition = /* model * */ a_position;
  v_normal = /* mat3(transpose(inverse(model))) * */ a_normal;
}
