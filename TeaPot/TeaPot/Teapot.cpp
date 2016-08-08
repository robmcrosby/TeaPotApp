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

Teapot::Teapot(): mCurModels(0), mCurMesh(0) {
}

Teapot::~Teapot() {
}

void Teapot::init() {
  mShader.loadFiles("physics.vert", "basic.frag");
  
  BufferMap bufferMap;
  ObjLoader::loadFile("teapot_low.obj", bufferMap);
  MeshUtils::addCenters(bufferMap, 3);
  mMeshes[0].loadBufferMap(bufferMap);
  
  ObjLoader::loadFile("teapot_med.obj", bufferMap);
  MeshUtils::addCenters(bufferMap, 3);
  mMeshes[1].loadBufferMap(bufferMap);
  
  ObjLoader::loadFile("teapot_high.obj", bufferMap);
  MeshUtils::addCenters(bufferMap, 3);
  mMeshes[2].loadBufferMap(bufferMap);
  
  mRotation = quat(vec3(1.0f, 0.0f, 0.0f), Pi/2.0f);
  
  mat4 rot = mRotation.toMat4();
  mat4 scale = mat4::Scale(vec3(4.0f, 4.0f, 4.0f));
  mModels[0].mInstances = 1;
  mModels[0].mMatrices[0] = rot * scale * mat4::Trans3d(vec3(0.0, -0.5, 0.0));
  
  scale = mat4::Scale(vec3(2.5f, 2.5f, 2.5f));
  mModels[1].mInstances = 2;
  mModels[1].mMatrices[0] = rot * scale * mat4::Trans3d(vec3(1.0, -0.5, 0.0));
  mModels[1].mMatrices[1] = rot * scale * mat4::Trans3d(vec3(-1.0, -0.5, 0.0));
  
  scale = mat4::Scale(vec3(2.0f, 2.0f, 2.0f));
  mModels[2].mInstances = 4;
  mModels[2].mMatrices[0] = rot * scale * mat4::Trans3d(vec3(1.0, -0.5, -0.7));
  mModels[2].mMatrices[1] = rot * scale * mat4::Trans3d(vec3(-1.0, -0.5, -0.7));
  mModels[2].mMatrices[2] = rot * scale * mat4::Trans3d(vec3(1.0, -0.5, 0.7));
  mModels[2].mMatrices[3] = rot * scale * mat4::Trans3d(vec3(-1.0, -0.5, 0.7));
  
  scale = mat4::Scale(vec3(1.5f, 1.5f, 1.5f));
  mModels[3].mInstances = 8;
  mModels[3].mMatrices[0] = rot * scale * mat4::Trans3d(vec3(1.0, -0.7, -0.7));
  mModels[3].mMatrices[1] = rot * scale * mat4::Trans3d(vec3(-1.0, -0.7, -0.7));
  mModels[3].mMatrices[2] = rot * scale * mat4::Trans3d(vec3(1.0, -0.7, 0.7));
  mModels[3].mMatrices[3] = rot * scale * mat4::Trans3d(vec3(-1.0, -0.7, 0.7));
  mModels[3].mMatrices[4] = rot * scale * mat4::Trans3d(vec3(1.0, 0.7, -0.7));
  mModels[3].mMatrices[5] = rot * scale * mat4::Trans3d(vec3(-1.0, 0.7, -0.7));
  mModels[3].mMatrices[6] = rot * scale * mat4::Trans3d(vec3(1.0, 0.7, 0.7));
  mModels[3].mMatrices[7] = rot * scale * mat4::Trans3d(vec3(-1.0, 0.7, 0.7));
}

void Teapot::bind() const {
  mShader.bind();
  mShader.setUniform("color", vec4(0.2f, 0.2f, 0.8f, 1.0f));
  mShader.setUniforms("models", mModels[mCurModels].mMatrices, 8);
  mShader.setUniform("rotation", mRotation.toVec4());
  mShader.setUniform("explosion", mExplosion);
}

void Teapot::draw() const {
  int instances = mModels[mCurModels].mInstances;
  mMeshes[mCurMesh].draw(mShader, instances);
}

void Teapot::setExplosionTime(float t) {
  mExplosion.w = t;
}

void Teapot::setExplosionCenter(const vec3 &center) {
  mExplosion.x = center.x;
  mExplosion.y = center.y;
  mExplosion.z = center.z;
}

void Teapot::setModelsSet(int index) {
  mCurModels = index;
}

void Teapot::setMesh(int index) {
  mCurMesh = index;
}

float Teapot::explosionTime() const {
  return mExplosion.w;
}

const Shader& Teapot::shader() const {
  return mShader;
}
