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
#include "Camera.h"
#include "Teapot.h"

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
  Camera mCamera;
  Teapot mTeapot;
  
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
  
  void countChange(int index);
  void triangleChange(int index);
  
private:
  void startExplosion(vec2 touch);
};


#endif /* Application_hpp */
