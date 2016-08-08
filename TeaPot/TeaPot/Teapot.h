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

#define MAX_INSTANCES 8
#define MAX_MODELS 4

struct Models {
  int mInstances;
  mat4 mMatrices[MAX_INSTANCES];
};


class Teapot {
  Shader mShader;
  Mesh mMesh;
  mat4 mModel;
  quat mRotation;
  vec4 mExplosion;
  
  int mCurModels;
  Models mModels[MAX_MODELS];
  
public:
  Teapot();
  ~Teapot();
  
  void init();
  void bind() const;
  void draw() const;
  
  void setExplosionTime(float t);
  void setExplosionCenter(const vec3 &center);
  void setModelsSet(int index);
  
  float explosionTime() const;
  const Shader& shader() const;
};


#endif /* Teapot_h */
