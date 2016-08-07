#version 100

attribute vec4 position;
attribute vec4 normal;
attribute vec4 center;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec4 rotation;

uniform vec3 camera;

uniform vec4 explosion;

varying vec3 v_normal;
varying vec3 v_camera;

vec3 rotate(vec4 q, vec3 v);

void main() {
  vec4 pos = model * position;
  vec4 cen = model * center;
  vec3 dir = cen.xyz - explosion.xyz;
  float len = length(dir);
  float force = max(1.0, 4.0 - len);
  float t = explosion.w;
  
  pos += vec4(dir/len * force*t, 0.0);
  pos.z -= 2.0 * explosion.w*explosion.w;
  
  gl_Position = projection * view * pos;
  v_normal = rotate(rotation, normal.xyz);
  v_camera = camera - pos.xyz;
}

vec3 rotate(vec4 q, vec3 v) {
  return v + 2.0 * cross(q.xyz, cross(q.xyz, v) + q.w * v);
}
