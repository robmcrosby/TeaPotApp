//
//  ObjLoader.h
//  TeaPot
//
//  Created by Robert Crosby on 8/5/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef ObjLoader_h
#define ObjLoader_h

#include "Mesh.h"
#include "VectorUtils.h"

struct Face {
  ivec3 positions;
  ivec3 normals;
};

class ObjLoader {
public:
  static bool loadFile(const std::string &filename, BufferMap &buffers);
  
private:
  static void parsePosition(const std::string line, std::vector<vec3> &positions);
  static void parseNormal(const std::string line, std::vector<vec3> &normals);
  static void parseFace(const std::string line, std::vector<Face> &faces);
  
  static void addVertex(const vec3 &vertex, Buffer &vertices);
};

#endif /* ObjLoader_hpp */
