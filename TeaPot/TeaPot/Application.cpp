//
//  Application.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "Application.h"
#include "GLIncludes.h"

using namespace std;

const float buffer[] = {
  -0.5f, -0.5f, 0.0f, 1.0f,
   0.5f, -0.5f, 0.0f, 1.0f,
   0.0f,  0.5f, 0.0f, 1.0f
};


Application& Application::instance() {
  static Application app;
  return app;
}

void Application::setup() {
  mTeaPotShader.loadFiles("basic.vert", "basic.frag");
  
  BufferMap bufferMap;
  bufferMap["position"] = Buffer(4, 3, buffer);
  mTeaPotMesh.loadBufferMap(bufferMap);
  
  glEnable(GL_DEPTH_TEST);
}

void Application::teardown() {
  
}

void Application::update(float time) {
  
}

void Application::render() {
  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
