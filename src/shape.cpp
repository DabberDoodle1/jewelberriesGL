#include "../include/shape.hpp"

#include <iostream>
#include <cmath>

Shape::Shape(std::vector<GLfloat> vertices, std::vector<GLfloat> colors, std::vector<GLuint> indices) {

  V = vertices;
  C = colors;
  I = indices;

  std::vector<GLfloat> hold;
  hold.insert(hold.end(), vertices.begin(), vertices.end());
  hold.insert(hold.end(), colors.begin(), colors.end());

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, hold.size() * sizeof(GLfloat), &hold[0], GL_DYNAMIC_DRAW);/*
  glBufferSubData(GL_ARRAY_BUFFER, 0, V.size() * sizeof(GLfloat), &V[0]);
  glBufferSubData(GL_ARRAY_BUFFER, V.size() * sizeof(GLfloat), C.size() * sizeof(GLfloat), &C[0]);*/
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, I.size() * sizeof(GLuint), &I[0], GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(V.size() * sizeof(GLfloat)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Shape::Draw() {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glDrawElements(GL_TRIANGLES, I.size(), GL_UNSIGNED_INT, (void*)0);
}

void Shape::PrintArr() {
  std::vector<GLfloat> stay;
  stay.insert(stay.end(), V.begin(), V.end());
  stay.insert(stay.end(), C.begin(), C.end());
  glGetBufferSubData(GL_ARRAY_BUFFER, 0, (V.size() + C.size()) * sizeof(GLfloat), &stay);

  for (int i=0;i<V.size()+C.size();i++) {
    std::cout << stay[i] << std::endl;
  }
}
