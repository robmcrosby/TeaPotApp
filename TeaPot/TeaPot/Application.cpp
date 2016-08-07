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
  
  mTeaPotShader.loadFiles("fracture.vert", "basic.frag");
  
  mDistance = 32.0f;
  mCenter = vec3(0.0f, 0.0f, 0.0f);
  mCamera = mCenter + vec3(1.0f, 1.0f, 1.0f).normalized() * mDistance;
  mView = mat4::LookAt(mCamera, mCenter, vec3(0.0f, 0.0f, 1.0f));
  
  BufferMap bufferMap;
  ObjLoader::loadFile("teapot.obj", bufferMap);
  //MeshUtils::addCenters(bufferMap, 1, 16);
  MeshUtils::addCenters(bufferMap, 6);
  mTeaPotMesh.loadBufferMap(bufferMap);
  mTeaPotRotation = quat(vec3(1.0f, 0.0f, 0.0f), Pi/2.0f);
  mTeaPotModel = mTeaPotRotation.toMat4() * mat4::Scale(vec3(4.0f, 4.0f, 4.0f)) * mat4::Trans3d(vec3(0.0, -0.5, 0.0));
  
  mExplosion.w = 1.0f;
  
  glEnable(GL_DEPTH_TEST);
}

void Application::teardown() {
  
}

void Application::update(float time) {
  switch (mState) {
    case DEFAULT:
      mExplosion.w = 0.0;
      break;
    case EXPLODING:
      mExplosion.w += 2.0f * time;
      if (mExplosion.w > 4.0f) {
        mExplosion.w = 4.0f;
        mState = IMPLODING;
      }
      break;
    case IMPLODING:
      mExplosion.w -= 2.0f * time;
      if (mExplosion.w < 0.0f) {
        mExplosion.w = 0.0f;
        mState = DEFAULT;
      }
      break;
    default:
      break;
  }
}

void Application::render() {
  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  mTeaPotShader.bind();
  mTeaPotShader.setUniform("color", vec4(0.2f, 0.2f, 0.8f, 1.0f));
  mTeaPotShader.setUniform("projection", mProjection);
  mTeaPotShader.setUniform("view", mView);
  mTeaPotShader.setUniform("model", mTeaPotModel);
  mTeaPotShader.setUniform("rotation", mTeaPotRotation.toVec4());
  mTeaPotShader.setUniform("camera", mCamera);
  mTeaPotShader.setUniform("explosion", mExplosion);
  mTeaPotMesh.draw(mTeaPotShader);
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
      mState = EXPLODING;
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
    default:
      break;
  }
}

void Application::handleMotion(float x, float y, float z, float w) {
  quat rot(x, y, z, w);
  vec3 up  = rot * vec3(0.0, 1.0, 0.0);
  
  mCamera = mCenter + rot * vec3(0.0, 0.0, 1.0) * mDistance;
  mView = mat4::LookAt(mCamera, mCenter, up);
}
