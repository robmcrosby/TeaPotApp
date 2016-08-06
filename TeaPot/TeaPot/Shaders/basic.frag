#version 100

uniform mediump vec4 color;

varying mediump vec3 v_normal;

void main() {
  //gl_FragColor = color;
  gl_FragColor = vec4(normalize(v_normal)/2.0 + 0.5, 1.0);
}
