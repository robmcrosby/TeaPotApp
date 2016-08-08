//
//  Application.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "Application.h"
#include "GLIncludes.h"
#include "ObjLoader.h"
#include "MeshUtils.h"

using namespace std;


Application& Application::instance() {
  static Application app;
  return app;
}

void Application::setup(float width, float height) {
  resize(width, height);
  
  mTeapot.init();
  
  mDistance = 16.0f;
  mCenter = vec3(0.0f, 0.0f, 0.0f);
  mCamera = mCenter + vec3(1.0f, 1.0f, 1.0f).normalized() * mDistance;
  mView = mat4::LookAt(mCamera, mCenter, vec3(0.0f, 0.0f, 1.0f));
  
  glEnable(GL_DEPTH_TEST);
}

void Application::teardown() {
  
}

void Application::update(float time) {
  float t = mTeapot.explosionTime();
  time *= 2.0f;
  
  switch (mState) {
    case DEFAULT:
      mTeapot.setExplosionTime(0.0f);
      break;
    case EXPLODING:
      t += time;
      if (t > 2.0f) {
        t = 2.0f;
        mState = IMPLODING;
      }
      mTeapot.setExplosionTime(t);
      break;
    case IMPLODING:
      t -= time;
      if (t < 0.0f) {
        t = 0.0f;
        mState = DEFAULT;
      }
      mTeapot.setExplosionTime(t);
      break;
    default:
      break;
  }
}

void Application::render() {
  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  mTeapot.bind();
  mTeapot.shader().setUniform("projection", mProjection);
  mTeapot.shader().setUniform("view", mView);
  mTeapot.shader().setUniform("camera", mCamera);
  mTeapot.draw();
}

void Application::resize(float width, float height) {
  float near = 4.0f;
  float far = 128.0f;
  
  mWindowSize.w = width;
  mWindowSize.h = height;
  
  width = 2.0f*width/height;
  height = 2.0f;
  
  mProjection = mat4::Frustum(-width, width, -height, height, near, far);
}

void Application::touchDown(float x, float y) {
  switch (mState) {
    case DEFAULT:
      startExplosion(vec2(x, y));
      break;
    case EXPLODING:
      mState = PAUSED_EXP;
      break;
    case IMPLODING:
      mState = PAUSED_IMP;
      break;
    case PAUSED_EXP:
      mState = EXPLODING;
      break;
    case PAUSED_IMP:
      mState = IMPLODING;
      break;
  }
}

void Application::handleMotion(float x, float y, float z, float w) {
  quat rot(x, y, z, w);
  vec3 up  = rot * vec3(0.0, 1.0, 0.0);
  
  mCamera = mCenter + rot * vec3(0.0, 0.0, 1.0) * mDistance;
  mView = mat4::LookAt(mCamera, mCenter, up);
}

void Application::startExplosion(vec2 touch) {
  touch /= mWindowSize;
  touch.y = (1.0f - touch.y);
  touch = touch*8.0f - vec2(4.0f, 4.0f);
  touch.y *= mWindowSize.h/mWindowSize.w;
  
  mat4 proj = mProjection * mView;
  vec4 center = proj * vec4(0.0, 0.0, 0.0, 1.0);
  center.x = touch.x;
  center.y = touch.y;
  center = proj.inverse() * center;
  center.w = 0;
  
  mTeapot.setExplosionCenter(center.xyz());
  mState = EXPLODING;
}
