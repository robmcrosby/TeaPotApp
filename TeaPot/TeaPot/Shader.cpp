//
//  Shader.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "Shader.h"


Shader::Shader(): mProgramId(0) {
  
}

Shader::~Shader() {
  unload();
}

bool Shader::loadFiles(const std::string &vert, const std::string &frag) {
  return false;
}

bool Shader::loadSrc(const std::string &vert, const std::string &frag) {
  return false;
}

void Shader::unload() {
  if (mProgramId > 0) {
    glDeleteProgram(mProgramId);
    mProgramId = 0;
  }
}
