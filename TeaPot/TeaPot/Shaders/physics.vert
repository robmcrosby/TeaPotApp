#version 100

#extension GL_ARB_draw_instanced : enable
#extension GL_EXT_draw_instanced : enable

attribute vec4 position;
attribute vec4 normal;
attribute vec4 center;

uniform mat4 projection;
uniform mat4 view;
uniform vec4 rotation;

uniform mat4 models[32];

uniform vec3 camera;

uniform vec4 explosion;

varying vec3 v_normal;
varying vec3 v_camera;

vec3 rotate(vec4 q, vec3 v);

void main() {
  mat4 model = models[gl_InstanceIDEXT];
  vec4 pos = model * position;
  vec4 cen = model * center;
  vec3 dir = cen.xyz - explosion.xyz;
  float len = length(dir);
  float force = max(2.0, 8.0 - len) + (1.0 + center.w*4.0);
  float t = explosion.w;
  
  // Apply Inital Explosion Force
  pos += vec4(dir/len * force*t, 0.0);
  
  // Apply Gravity
  pos.z -= 8.0*t*t;
  
  gl_Position = projection * view * pos;
  v_normal = rotate(rotation, normal.xyz);
  v_camera = camera - pos.xyz;
}

vec3 rotate(vec4 q, vec3 v) {
  return v + 2.0 * cross(q.xyz, cross(q.xyz, v) + q.w * v);
}
