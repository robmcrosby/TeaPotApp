//
//  Shader.hpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <iostream>
#include "GLIncludes.h"


class Shader {
  GLuint mProgramId;
  
public:
  Shader();
  ~Shader();
  
  void bind() const;
  GLuint programId() const;
  
  bool loadFiles(const std::string &vert, const std::string &frag);
  bool loadSrc(const std::string &vert, const std::string &frag);
  
  void unload();
  
private:
  GLuint compilePart(const char *src, GLenum type);
  void checkPart(GLuint partId, const char *src);
  void deleteParts(GLuint *parts);
  
  void buildProgram(GLuint *parts);
  void attachParts(GLuint *parts);
  void detachParts(GLuint *parts);
  void checkProgram();
};


#endif /* Shader_h */
