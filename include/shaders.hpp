#ifndef SHADERS
#define SHADERS

#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <string>
#include <iostream>

class Shaders {
public:
  unsigned int shaderProgram;
  Shaders(const char *vsSource, const char *fsSource);
  void checkCompileErrors(unsigned int shader, std::string type);
};
#endif
