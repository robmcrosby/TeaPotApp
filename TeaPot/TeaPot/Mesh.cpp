//
//  Mesh.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "Mesh.h"
#include "Shader.h"

using namespace std;


Mesh::Mesh(): mCount(0), mVertexArray(0) {
  
}

Mesh::~Mesh() {
  
}

void Mesh::draw(const Shader &shader, int instances) const {
  GLuint programId = shader.programId();
  
  glBindVertexArray(mVertexArray);
  for (const auto &buffer : mVertexBuffers)
  {
    GLint index = glGetAttribLocation(programId, buffer.first.c_str());
    if (index >= 0)
    {
      glBindBuffer(GL_ARRAY_BUFFER, buffer.second.bufferId);
      glEnableVertexAttribArray(index);
      glVertexAttribPointer(index, buffer.second.components, GL_FLOAT, GL_FALSE, 0, 0);
    }
  }
  
  glDrawArraysInstanced(GL_TRIANGLES, 0, mCount, instances);
  glBindVertexArray(0);
}

bool Mesh::loadBufferMap(const BufferMap &bufferMap) {
  bool success = true;
  unload();
  
  glGenVertexArrays(1, &mVertexArray);
  glBindVertexArray(mVertexArray);
  
  for (const auto &buffer : bufferMap) {
    success &= loadBuffer(buffer.first, buffer.second);
  }
  
  return success;
}

bool Mesh::loadBuffer(const string &name, const Buffer &buffer) {
  VertexBuffer vertBuf;
  vertBuf.components = buffer.components;
  
  mCount = buffer.count();
  
  glGenBuffers(1, &vertBuf.bufferId);
  if (!vertBuf.bufferId)
  {
    cerr << "Error Creating Vertex Buffer." << endl;
    return false;
  }
  
  GLsizeiptr size = vertBuf.components * mCount * sizeof(float);
  const GLvoid *ptr = (const GLvoid*)buffer.ptr();
  
  glBindBuffer(GL_ARRAY_BUFFER, vertBuf.bufferId);
  glBufferData(GL_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  mVertexBuffers[name] = vertBuf;
  return true;
}

void Mesh::unload() {
  glDeleteVertexArrays(1, &mVertexArray);
  mVertexArray = 0;
  
  for (auto &buffer : mVertexBuffers) {
    glDeleteBuffers(1, &buffer.second.bufferId);
  }
  mVertexBuffers.clear();
  mCount = 0;
}
