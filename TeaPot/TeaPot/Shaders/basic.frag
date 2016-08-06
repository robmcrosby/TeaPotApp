#version 100

uniform mediump vec4 color;

varying mediump vec3 v_normal;
varying mediump vec3 v_camera;

void main() {
  mediump vec3 light = vec3(0.0, 1.0, 0.0);
  mediump vec3 normal = normalize(v_normal);
  mediump vec3 ref = normalize(-reflect(light, normal));
  mediump vec3 camera = normalize(v_camera);
  
  mediump float diffuse = max(dot(light, normal), 0.0);
  mediump float specular = pow(max(dot(ref, camera), 0.0), 10.0);
  
  gl_FragColor = vec4(min(diffuse+0.4, 1.0)*color.xyz + vec3(specular), 1.0);
}
