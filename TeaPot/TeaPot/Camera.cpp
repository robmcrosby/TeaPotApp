//
//  Camera.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/7/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "Camera.h"


using namespace std;


Camera::Camera() {
  mDistance = 16.0f;
  mTarget = vec3(0.0f, 0.0f, 0.0f);
  mUp = vec3(0.0f, 0.0f, 1.0f);
  
  mPosition = mTarget + vec3(1.0f, 1.0f, 1.0f).normalized() * mDistance;
  mView = mat4::LookAt(mPosition, mTarget, mUp);
}

Camera::~Camera() {
  
}

void Camera::resize(vec2 window) {
  mWindowSize = window;
  
  float near = 4.0f;
  float far = 128.0f;
  
  float width = 2.0f*window.w/window.h;
  float height = 2.0f;
  
  mProjection = mat4::Frustum(-width, width, -height, height, near, far);
}

void Camera::rotate(quat rot) {
  mUp = rot * vec3(0.0, 1.0, 0.0);
  mPosition = mTarget + rot * vec3(0.0, 0.0, 1.0) * mDistance;
  mView = mat4::LookAt(mPosition, mTarget, mUp);
}

void Camera::bind(const Shader &shader) const {
  shader.setUniform("projection", mProjection);
  shader.setUniform("view", mView);
  shader.setUniform("camera", mPosition);
}

vec3 Camera::getTouchLocation(vec2 touch) const {
  touch /= mWindowSize;
  touch.y = (1.0f - touch.y);
  touch = touch*8.0f - vec2(4.0f, 4.0f);
  touch.y *= mWindowSize.h/mWindowSize.w;
  
  mat4 proj = mProjection * mView;
  vec4 center = proj * vec4(0.0, 0.0, 0.0, 1.0);
  center.x = touch.x;
  center.y = touch.y;
  center = proj.inverse() * center;
  
  return center.xyz();
}
