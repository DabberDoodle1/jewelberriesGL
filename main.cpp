#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "include/shaders.hpp"

void FBSC(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

float D2V(float deg, bool sinxcos, double radius) {
  if (sinxcos)
    return (float)radius * sin(deg * M_PI/180);
  else
    return (float)radius * cos(deg * M_PI/180);
}

int main(void) {


  if (!glfwInit()) {
    std::cout << "ERROR: GLFW not initialized because glfwInit() has failed." << std::endl;
    return -1;
  }


  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  GLFWwindow *window =
      glfwCreateWindow(720, 720, "Jewelberries on OpenGL", NULL, NULL);
  if (!window) {
    std::cout << "ERROR: Window not initialized because glfwCreateWindow() has failed." << std::endl;
    glfwTerminate();
    return -1;
  }


  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, FBSC);


  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "ERROR: GLAD not initialized because gladLoadGLLoader() has failed." << std::endl;
    return -1;
  }


  float vertices[] = {
    D2V(120, false, 1/sqrt(2)), D2V(120, true, 1/sqrt(2)), 0.0f, 0.5f, 1.0f, 0.0f, 
    D2V(210, false, 1/sqrt(2)), D2V(210, true, 1/sqrt(2)), 0.0f, 0.0f, 1.0f, 1.0f,

    D2V(30, false, 1/sqrt(2)), D2V(30, true, 1/sqrt(2)), 0.0f, 1.0f, 0.0f, 0.0f,

    D2V(300, false, 1/sqrt(2)), D2V(300, true, 1/sqrt(2)), 0.0f, 1.0f, 0.0f, 0.5f,
    D2V(210, false, 1/sqrt(2)), D2V(210, true, 1/sqrt(2)), 0.0f, 0.0f, 1.0f, 1.0f,

    D2V(120, false, 0.2/sqrt(2)), D2V(120, true, 0.2/sqrt(2)), 0.0f, 229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f, 
    D2V(210, false, 0.2/sqrt(2)), D2V(210, true, 0.2/sqrt(2)), 0.0f, 229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f,

    D2V(30, false, 0.2/sqrt(2)), D2V(30, true, 0.2/sqrt(2)), 0.0f, 229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f,

    D2V(300, false, 0.2/sqrt(2)), D2V(300, true, 0.2/sqrt(2)), 0.0f, 229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f,
    D2V(210, false, 0.2/sqrt(2)), D2V(210, true, 0.2/sqrt(2)), 0.0f, 229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f
  };


  unsigned int buffer, vArray;
  glGenVertexArrays(1, &vArray);
  glGenBuffers(1, &buffer);
  glBindVertexArray(vArray);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  Shaders shaders("src/shaders/shaders.vs", "src/shaders/shaders.fs");


  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    glClearColor(229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaders.shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 2, 3);
    glDrawArrays(GL_TRIANGLES, 5, 3);
    glDrawArrays(GL_TRIANGLES, 7, 3);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }


  glfwTerminate();
  return 0;
}
