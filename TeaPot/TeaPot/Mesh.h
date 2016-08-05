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
#include <OpenGLES/ES2/glext.h>


struct Buffer {
  std::vector<float> data;
  int components;
  
  Buffer(): components(1) {}
  Buffer(int comps, int count, const float *data): data(comps*count), components(comps) {
    memcpy(ptr(), data, size()*sizeof(float));
  }
  int size() const {return (int)data.size();}
  int count() const {return size()/components;}
  float* ptr() {return &data[0];}
};
typedef std::map<std::string, Buffer> BufferMap;

class Mesh {
  
public:
  Mesh();
  ~Mesh();
  
  bool loadBufferMap(BufferMap &bufferMap);
  void unload();
};

#endif /* Mesh_h */
