//
//  ObjLoader.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/5/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "ObjLoader.h"
#include "StringUtils.h"


using namespace std;

bool ObjLoader::loadFile(const string &filename, BufferMap &buffers) {
  stringstream contents(StringUtils::ReadTextFile(filename));
  string line;
  
  vector<vec3> positions;
  vector<vec3> normals;
  vector<Face> faces;
  
  while (getline(contents, line, '\n')) {
    if (line.size() > 0) {
      if (line[0] == 'v') {
        if (line[1] == 'n')
          parseNormal(line, normals);
        else
          parsePosition(line, positions);
      }
      else if (line[0] == 'f')
        parseFace(line, faces);
    }
  }
  
  buffers.clear();
  buffers["position"] = Buffer();
  buffers["position"].components = 4;
  
  buffers["normal"] = Buffer();
  buffers["normal"].components = 4;
  
  for (Face face : faces) {
    addVertex(positions[face.positions.x], buffers["position"]);
    addVertex(positions[face.positions.y], buffers["position"]);
    addVertex(positions[face.positions.z], buffers["position"]);
    
    addVertex(normals[face.normals.x], buffers["normal"]);
    addVertex(normals[face.normals.y], buffers["normal"]);
    addVertex(normals[face.normals.z], buffers["normal"]);
  }
  
  return true;
}

void ObjLoader::parsePosition(const std::string line, std::vector<vec3> &positions) {
  vec3 pos;
  sscanf(line.c_str(), "v %f %f %f ", &pos.x, &pos.y, &pos.z);
  
  positions.push_back(pos);
}

void ObjLoader::parseNormal(const std::string line, std::vector<vec3> &normals) {
  vec3 norm;
  sscanf(line.c_str(), "vn %f %f %f ", &norm.x, &norm.y, &norm.z);
  
  normals.push_back(norm);
}

void ObjLoader::parseFace(const std::string line, std::vector<Face> &faces) {
  Face face;
  sscanf(line.c_str(), "f %i//%i %i//%i %i//%i",
         &face.positions.x, &face.normals.x,
         &face.positions.y, &face.normals.y,
         &face.positions.z, &face.normals.z);
  
  // Objs are not zero indexed
  face.positions -= ivec3(1, 1, 1);
  face.normals -= ivec3(1, 1, 1);
  
  faces.push_back(face);
}

void ObjLoader::addVertex(const vec3 &vertex, Buffer &vertices) {
  vertices.data.push_back(vertex.x);
  vertices.data.push_back(vertex.y);
  vertices.data.push_back(vertex.z);
  vertices.data.push_back(1.0f);
}


