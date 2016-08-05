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
#include <OpenGLES/ES2/glext.h>


class Shader {
  GLuint mProgramId;
  
public:
  Shader();
  ~Shader();
  
  bool loadFiles(const std::string &vert, const std::string &frag);
  bool loadSrc(const std::string &vert, const std::string &frag);
  
  void unload();
};


#endif /* Shader_h */
