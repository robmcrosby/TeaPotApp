//
//  MeshUtils.h
//  TeaPot
//
//  Created by Robert Crosby on 8/6/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef MeshUtils_h
#define MeshUtils_h

#include "Mesh.h"


struct MeshUtils {
  static void addCenters(BufferMap &buffers, int groups) {
    std::vector<vec3> positions;
    std::vector<vec3> centers;
    
    groups *= 3;
    
    extract(buffers["position"], positions);
    
    for (int i = 0; i < (int)positions.size()/groups; ++i) {
      int count = 1;
      int index = i*groups;
      
      // Iterate the group to find the average position
      vec3 avg = positions[index];
      while (++index < (int)positions.size() && ++count < groups) {
        avg += positions[index];
      }
      avg /= (float)count;
      
      // Add the average position as centers
      for (int j = 0; j < groups; ++j) {
        centers.push_back(avg);
      }
    }
    
    pack(buffers["center"], centers, 1.0);
  }
  
  static void extract(const Buffer &buffer, std::vector<vec3> &array) {
    const std::vector<float> &data = buffer.data;
    
    for(int i = 0; i < buffer.count(); ++i) {
      int index = i*buffer.components;
      array.push_back(vec3(data[index], data[index+1], data[index+2]));
    }
  }
  
  static void pack(Buffer &buffer, const std::vector<vec3> &array, float w) {
    buffer.data.clear();
    buffer.components = 4;
    
    for (const vec3 v : array) {
      buffer.data.push_back(v.x);
      buffer.data.push_back(v.y);
      buffer.data.push_back(v.z);
      buffer.data.push_back(w);
    }
  }
};

#endif /* MeshUtils_h */
