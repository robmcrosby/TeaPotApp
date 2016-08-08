//
//  Teapot.h
//  TeaPot
//
//  Created by Robert Crosby on 8/7/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef Teapot_h
#define Teapot_h

#include "Mesh.h"
#include "Shader.h"


class Teapot {
  Shader mShader;
  Mesh mMesh;
  mat4 mModel;
  quat mRotation;
  vec4 mExplosion;
  
public:
  Teapot();
  ~Teapot();
  
  void init();
  void bind() const;
  void draw() const;
  
  void setExplosionTime(float t);
  void setExplosionCenter(const vec3 &center);
  
  float explosionTime() const;
  const Shader& shader() const;
};


#endif /* Teapot_h */
