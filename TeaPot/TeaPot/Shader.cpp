//
//  Shader.cpp
//  TeaPot
//
//  Created by Robert Crosby on 8/4/16.
//  Copyright © 2016 Robert Crosby. All rights reserved.
//

#include "Shader.h"
#include "StringUtils.h"

#define ERROR_MSG_SIZE 512

using namespace std;


Shader::Shader(): mProgramId(0) {
  
}

Shader::~Shader() {
  unload();
}

void Shader::bind() const {
  glUseProgram(mProgramId);
}

GLuint Shader::programId() const {
  return mProgramId;
}

void Shader::setUniform(const std::string &name, const float &v) const {
  setUniform(name, &v, 1);
}

void Shader::setUniform(const std::string &name, const float *v, int size) const {
  GLint loc = glGetUniformLocation(mProgramId, name.c_str());
  if (loc >= 0) {
    glUniform1fv(loc, (GLsizei)size, (const GLfloat*)v);
  }
}

void Shader::setUniform(const std::string &name, const vec2 &v) const {
  GLint loc = glGetUniformLocation(mProgramId, name.c_str());
  if (loc >= 0) {
    glUniform2fv(loc, 1, (const GLfloat*)v.ptr());
  }
}

void Shader::setUniform(const std::string &name, const vec3 &v) const {
  GLint loc = glGetUniformLocation(mProgramId, name.c_str());
  if (loc >= 0) {
    glUniform3fv(loc, 1, (const GLfloat*)v.ptr());
  }
}

void Shader::setUniform(const std::string &name, const vec4 &v) const {
  GLint loc = glGetUniformLocation(mProgramId, name.c_str());
  if (loc >= 0) {
    glUniform4fv(loc, 1, (const GLfloat*)v.ptr());
  }
}

void Shader::setUniform(const std::string &name, const mat4 &m) const {
  GLint loc = glGetUniformLocation(mProgramId, name.c_str());
  if (loc >= 0) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*)m.ptr());
  }
}

void Shader::setUniforms(const std::string &name, const mat4 *m, int count) const {
  GLint loc = glGetUniformLocation(mProgramId, name.c_str());
  if (loc >= 0) {
    glUniformMatrix4fv(loc, count, GL_FALSE, (const GLfloat*)m->ptr());
  }
}

bool Shader::loadFiles(const std::string &vert, const std::string &frag) {
  string vSrc = StringUtils::ReadTextFile(vert);
  string fSrc = StringUtils::ReadTextFile(frag);
  return loadSrc(vSrc, fSrc);
}

bool Shader::loadSrc(const std::string &vert, const std::string &frag) {
  // Compile the shader program parts
  GLuint parts[2];
  parts[0] = compilePart(vert.c_str(), GL_VERTEX_SHADER);
  parts[1] = compilePart(frag.c_str(), GL_FRAGMENT_SHADER);
  
  buildProgram(parts);
  deleteParts(parts);
  return true;
}

void Shader::unload() {
  if (mProgramId > 0) {
    glDeleteProgram(mProgramId);
    mProgramId = 0;
  }
}

GLuint Shader::compilePart(const char *src, GLenum type) {
  GLuint partId = glCreateShader(type);
  if (partId > 0) {
    glShaderSource(partId, 1, &src, 0);
    glCompileShader(partId);
    checkPart(partId, src);
  }
  else {
    std::cerr << "Error creating OpenGL Shader" << std::endl;
  }
  return partId;
}

void Shader::checkPart(GLuint partId, const char *src)
{
  GLint compileSuccess;
  glGetShaderiv(partId, GL_COMPILE_STATUS, &compileSuccess);
  if (compileSuccess == GL_FALSE) {
    GLchar messages[ERROR_MSG_SIZE];
    glGetShaderInfoLog(partId, sizeof(messages), 0, &messages[0]);
    cerr << messages << endl;
    cerr << src << endl;
  }
}

void Shader::deleteParts(GLuint *parts)
{
  for (int i = 0; i < 2; ++i) {
    if (parts[i] > 0)
      glDeleteShader(parts[i]);
    parts[i] = 0;
  }
}

void Shader::buildProgram(GLuint *parts) {
  mProgramId = glCreateProgram();
  if (mProgramId > 0) {
    attachParts(parts);
    glLinkProgram(mProgramId);
    detachParts(parts);
    checkProgram();
  }
  else {
    cerr << "Error: Unable to create OpenGL Program" << endl;
  }
}

void Shader::attachParts(GLuint *parts) {
  for (int i = 0; i < 2; ++i) {
    if (parts[i] > 0)
      glAttachShader(mProgramId, parts[i]);
  }
}

void Shader::detachParts(GLuint *parts) {
  for (int i = 0; i < 2; ++i) {
    if (parts[i] > 0)
      glDetachShader(mProgramId, parts[i]);
  }
}

void Shader::checkProgram() {
  GLint linkSuccess;
  glGetProgramiv(mProgramId, GL_LINK_STATUS, &linkSuccess);
  if (linkSuccess == GL_FALSE) {
    GLchar messages[ERROR_MSG_SIZE];
    glGetProgramInfoLog(mProgramId, sizeof(messages), 0, &messages[0]);
    cerr << messages << endl;
  }
}
