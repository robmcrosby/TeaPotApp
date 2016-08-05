//
//  Shader.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "Shader.h"
#include "StringUtils.h"

using namespace std;


Shader::Shader(): mProgramId(0) {
  
}

Shader::~Shader() {
  unload();
}

bool Shader::loadFiles(const std::string &vert, const std::string &frag) {
  string vSrc = StringUtils::ReadTextFile(vert);
  string fSrc = StringUtils::ReadTextFile(frag);
  return loadSrc(vSrc, fSrc);
}

bool Shader::loadSrc(const std::string &vert, const std::string &frag) {
  cout << vert << endl;
  cout << frag << endl;
  return true;
}

void Shader::unload() {
  if (mProgramId > 0) {
    glDeleteProgram(mProgramId);
    mProgramId = 0;
  }
}
