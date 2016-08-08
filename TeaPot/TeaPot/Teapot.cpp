//
//  Teapot.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/7/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "Teapot.h"
#include "ObjLoader.h"
#include "MeshUtils.h"


using namespace std;

Teapot::Teapot() {
}

Teapot::~Teapot() {
}

void Teapot::init() {
  mShader.loadFiles("physics.vert", "basic.frag");
  
  BufferMap bufferMap;
  ObjLoader::loadFile("teapot.obj", bufferMap);
  MeshUtils::addCenters(bufferMap, 3);
  mMesh.loadBufferMap(bufferMap);
  mRotation = quat(vec3(1.0f, 0.0f, 0.0f), Pi/2.0f);
  
//  mModel = mRotation.toMat4() * mat4::Scale(vec3(4.0f, 4.0f, 4.0f)) * mat4::Trans3d(vec3(0.0, -0.5, 0.0));
  
  mModels[0] = mRotation.toMat4() * mat4::Scale(vec3(2.5f, 2.5f, 2.5f)) * mat4::Trans3d(vec3(1.0, -0.5, 0.0));
  mModels[1] = mRotation.toMat4() * mat4::Scale(vec3(2.5f, 2.5f, 2.5f)) * mat4::Trans3d(vec3(-1.0, -0.5, 0.0));
  
//  mModels[0] = mRotation.toMat4() * mat4::Scale(vec3(2.0f, 2.0f, 2.0f)) * mat4::Trans3d(vec3(1.0, -0.5, -0.7));
//  mModels[1] = mRotation.toMat4() * mat4::Scale(vec3(2.0f, 2.0f, 2.0f)) * mat4::Trans3d(vec3(-1.0, -0.5, -0.7));
//  mModels[2] = mRotation.toMat4() * mat4::Scale(vec3(2.0f, 2.0f, 2.0f)) * mat4::Trans3d(vec3(1.0, -0.5, 0.7));
//  mModels[3] = mRotation.toMat4() * mat4::Scale(vec3(2.0f, 2.0f, 2.0f)) * mat4::Trans3d(vec3(-1.0, -0.5, 0.7));
  
//  mModels[0] = mRotation.toMat4() * mat4::Scale(vec3(1.5f, 1.5f, 1.5f)) * mat4::Trans3d(vec3(1.0, -0.7, -0.7));
//  mModels[1] = mRotation.toMat4() * mat4::Scale(vec3(1.5f, 1.5f, 1.5f)) * mat4::Trans3d(vec3(-1.0, -0.7, -0.7));
//  mModels[2] = mRotation.toMat4() * mat4::Scale(vec3(1.5f, 1.5f, 1.5f)) * mat4::Trans3d(vec3(1.0, -0.7, 0.7));
//  mModels[3] = mRotation.toMat4() * mat4::Scale(vec3(1.5f, 1.5f, 1.5f)) * mat4::Trans3d(vec3(-1.0, -0.7, 0.7));
//  mModels[4] = mRotation.toMat4() * mat4::Scale(vec3(1.5f, 1.5f, 1.5f)) * mat4::Trans3d(vec3(1.0, 0.7, -0.7));
//  mModels[5] = mRotation.toMat4() * mat4::Scale(vec3(1.5f, 1.5f, 1.5f)) * mat4::Trans3d(vec3(-1.0, 0.7, -0.7));
//  mModels[6] = mRotation.toMat4() * mat4::Scale(vec3(1.5f, 1.5f, 1.5f)) * mat4::Trans3d(vec3(1.0, 0.7, 0.7));
//  mModels[7] = mRotation.toMat4() * mat4::Scale(vec3(1.5f, 1.5f, 1.5f)) * mat4::Trans3d(vec3(-1.0, 0.7, 0.7));
}

void Teapot::bind() const {
  mShader.bind();
  mShader.setUniform("color", vec4(0.2f, 0.2f, 0.8f, 1.0f));
  mShader.setUniforms("models", mModels, 32);
  mShader.setUniform("rotation", mRotation.toVec4());
  mShader.setUniform("explosion", mExplosion);
}

void Teapot::draw() const {
  mMesh.draw(mShader, 2);
}

void Teapot::setExplosionTime(float t) {
  mExplosion.w = t;
}

void Teapot::setExplosionCenter(const vec3 &center) {
  mExplosion.x = center.x;
  mExplosion.y = center.y;
  mExplosion.z = center.z;
}

float Teapot::explosionTime() const {
  return mExplosion.w;
}

const Shader& Teapot::shader() const {
  return mShader;
}
