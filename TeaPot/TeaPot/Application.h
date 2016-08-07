//
//  Application.hpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <iostream>
#include "Shader.h"
#include "Mesh.h"

enum APP_STATE {
  DEFAULT,
  EXPLODING,
  IMPLODING,
  PAUSED_EXP,
  PAUSED_IMP,
};

/**
 * Singleton that controls the high level logic of the Application.
 */
class Application {
  vec2 mWindowSize;
  
  vec3 mCamera;
  vec3 mCenter;
  float mDistance;
  
  mat4 mProjection;
  mat4 mView;
  
  Shader mTeaPotShader;
  Mesh mTeaPotMesh;
  mat4 mTeaPotModel;
  quat mTeaPotRotation;
  
  vec4 mExplosion;
  APP_STATE mState;
  
private:
  Application(): mState(DEFAULT) {}
  Application(const Application&) {}
  ~Application() {}
  Application& operator=(const Application&) {return *this;}
  
public:
  static Application& instance();
  
  void setup(float width, float height);
  void teardown();
  
  void update(float time);
  void render();
  
  void resize(float width, float height);
  
  void touchDown(float x, float y);
  void handleMotion(float x, float y, float z, float w);
};


#endif /* Application_hpp */
