#version 100

attribute vec4 position;
attribute vec4 normal;
attribute vec4 center;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 camera;

varying vec3 v_normal;
varying vec3 v_camera;

void main() {
  vec4 pos = model * position;
  vec4 cen = model * center;
  
  pos += vec4(normalize(cen.xyz)*0.1, 0.0);
  
  gl_Position = projection * view * pos;
  v_normal = normal.xyz;
  v_camera = camera - pos.xyz;
}
