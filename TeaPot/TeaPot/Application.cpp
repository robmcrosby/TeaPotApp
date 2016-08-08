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
  mCamera.bind(mTeapot.shader());
  mTeapot.draw();
}

void Application::resize(float width, float height) {
  mCamera.resizeWindow(vec2(width, height));
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
  mCamera.rotate(rot);
}

void Application::startExplosion(vec2 touch) {
  vec3 center = mCamera.getTouchLocation(touch);
  mTeapot.setExplosionCenter(center);
  mState = EXPLODING;
}
