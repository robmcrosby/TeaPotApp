//
//  Camera.h
//  TeaPot
//
//  Created by Robert Crosby on 8/7/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Shader.h"


class Camera {
  vec2 mWindowSize;
  
  vec3 mPosition;
  vec3 mTarget;
  vec3 mUp;
  float mDistance;
  
  mat4 mProjection;
  mat4 mView;
  
public:
  Camera();
  ~Camera();
  
  void resize(vec2 window);
  void rotate(quat rot);
  
  void bind(const Shader &shader) const;
  
  vec3 getTouchLocation(vec2 touch) const;
};

#endif /* Camera_h */
