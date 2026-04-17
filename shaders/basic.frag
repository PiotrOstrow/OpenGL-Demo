#version 410

in vec3 color;

out vec4 outputColor;

uniform float u_time;

void main() {
  outputColor = vec4(color, 1.0);
  outputColor.rgb *= 0.5 + sin(u_time * 2.0) * 0.5;
}
