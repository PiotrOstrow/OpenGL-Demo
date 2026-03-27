#version 410

uniform float u_time;
uniform uint u_viewPosition;

in vec3 v_normal;
in vec3 v_fragmentPosition;

out vec4 outputColor;

void main() {
  float ambient = 0.2;
  vec3 lightDir = normalize(vec3(-1.0, -1.0, 0.0));
  //vec3 lightDir = normalize(vec3(cos(u_time), -2.0, sin(u_time)));

  vec3 normal = normalize(v_normal);
  float diff = max(dot(normal, -lightDir), 0.0);
  vec3 color = (ambient + diff) * vec3(1.0);

  //color = normal;

  outputColor = vec4(color, 1.0);
}


