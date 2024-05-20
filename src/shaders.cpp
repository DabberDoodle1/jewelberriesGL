#include "../include/shaders.hpp"

Shaders::Shaders(const char *vsSource, const char *fsSource) {
  std::string source;
  std::ifstream fileStream;
  std::stringstream vSourceStream, fSourceStream;
  unsigned int vertexShader, fragmentShader;
  const char *vShaderSource;
  const char *fShaderSource;

  fileStream.open(vsSource);
  vSourceStream << fileStream.rdbuf();
  fileStream.close();

  source = vSourceStream.str();
  vShaderSource = source.c_str();
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderSource, NULL);
  glCompileShader(vertexShader);
  checkCompileErrors(vertexShader, "VERTEX");

  fileStream.open(fsSource);
  fSourceStream << fileStream.rdbuf();
  fileStream.close();

  source = fSourceStream.str();
  fShaderSource = source.c_str();
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkCompileErrors(fragmentShader, "FRAGMENT");

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  checkCompileErrors(shaderProgram, "PROGRAM");
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shaders::checkCompileErrors(unsigned int shader, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
}
