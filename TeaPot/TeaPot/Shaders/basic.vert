#version 100

attribute vec4 position;
attribute vec4 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec3 v_normal;

void main() {
  gl_Position = projection * view * model * position;
  v_normal = normal.xyz;
}
