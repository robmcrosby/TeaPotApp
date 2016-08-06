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

using namespace std;


Application& Application::instance() {
  static Application app;
  return app;
}

void Application::setup(float width, float height) {
  resize(width, height);
  
  mTeaPotShader.loadFiles("basic.vert", "basic.frag");
  
  mCamera = vec3(10.0f, 10.0f, 10.0f);
  mCenter = vec3(0.0f, 0.0f, 0.0f);
  mView = mat4::LookAt(mCamera, mCenter, vec3(0.0f, 1.0f, 0.0f));
  
  BufferMap bufferMap;
  ObjLoader::loadFile("teapot.obj", bufferMap);
  mTeaPotMesh.loadBufferMap(bufferMap);
  mTeaPotModel = mat4::Scale(vec3(4.0f, 4.0f, 4.0f)) * mat4::Trans3d(vec3(0.0, -0.5, 0.0));
  
  glEnable(GL_DEPTH_TEST);
}

void Application::teardown() {
  
}

void Application::update(float time) {
  
}

void Application::render() {
  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  mTeaPotShader.bind();
  mTeaPotShader.setUniform("color", vec4(0.2f, 0.2f, 0.8f, 1.0f));
  mTeaPotShader.setUniform("projection", mProjection);
  mTeaPotShader.setUniform("view", mView);
  mTeaPotShader.setUniform("model", mTeaPotModel);
  mTeaPotShader.setUniform("camera", mCamera);
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
