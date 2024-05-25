#ifndef SHAPE
#define SHAPE

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Shape {
public:
  Shape(std::vector<GLfloat> vertices, std::vector<GLfloat> colors, std::vector<GLuint> indices);
  void Draw();
  void PrintArr();
  std::vector<GLfloat> V, C;
  std::vector<GLuint> I;
private:
  GLuint VBO, VAO, EBO;
};
#endif
