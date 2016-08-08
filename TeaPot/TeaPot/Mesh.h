//
//  Mesh.h
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <iostream>
#include <vector>
#include <map>

#include "GLIncludes.h"

class Shader;

struct Buffer {
  std::vector<float> data;
  int components;
  
  Buffer(): components(1) {}
  Buffer(int comps, int count, const float *data): data(comps*count), components(comps) {
    memcpy(ptr(), data, size()*sizeof(float));
  }
  int size() const {return (int)data.size();}
  int count() const {return size()/components;}
  const float* ptr() const {return &data[0];}
  float* ptr() {return &data[0];}
};
typedef std::map<std::string, Buffer> BufferMap;


struct VertexBuffer {
  GLuint components;
  GLuint bufferId;
  
  VertexBuffer(): components(0), bufferId(0) {}
};
typedef std::map<std::string, VertexBuffer> VertexBufferMap;


class Mesh {
  GLuint mCount;
  GLuint mVertexArray;
  VertexBufferMap mVertexBuffers;
  
public:
  Mesh();
  ~Mesh();
  
  void draw(const Shader &shader, int instances = 1) const;
  
  bool loadBufferMap(const BufferMap &bufferMap);
  void unload();
  
private:
  bool loadBuffer(const std::string &name, const Buffer &buffer);
};

#endif /* Mesh_h */
