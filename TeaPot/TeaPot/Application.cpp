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

void Application::setup() {
  mTeaPotShader.loadFiles("basic.vert", "basic.frag");
  
  BufferMap bufferMap;
  ObjLoader::loadFile("teapot.obj", bufferMap);
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
  
  mTeaPotShader.bind();
  mTeaPotShader.setUniform("color", vec4(0.2f, 0.2f, 0.8f, 1.0f));
  mTeaPotMesh.draw(mTeaPotShader);
}
