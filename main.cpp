#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "include/shaders.hpp"

float pt1 = 30;
float pt2 = 120;
float pt3 = 210;
float pt4 = 300;

void FBSC(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

float D2V(float deg, bool sinxcos, double radius) {
  if (sinxcos)
    return (float)radius * sin(deg * M_PI/180);
  else
    return (float)radius * cos(deg * M_PI/180);
}

void Increment(float &num) {
  num--;
  if (num == 360)
    num = 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_RELEASE)
    return;
  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(window, true);
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
    D2V(pt2, false, 1/sqrt(2)), D2V(pt2, true, 1/sqrt(2)), 0.0f,
    D2V(pt3, false, 1/sqrt(2)), D2V(pt3, true, 1/sqrt(2)), 0.0f,
    D2V(pt1, false, 1/sqrt(2)), D2V(pt1, true, 1/sqrt(2)), 0.0f,
    D2V(pt4, false, 1/sqrt(2)), D2V(pt4, true, 1/sqrt(2)), 0.0f,
    D2V(pt3, false, 1/sqrt(2)), D2V(pt3, true, 1/sqrt(2)), 0.0f,

    D2V(pt2, false, 0.2/sqrt(2)), D2V(pt2, true, 0.2/sqrt(2)), 0.0f,
    D2V(pt3, false, 0.2/sqrt(2)), D2V(pt3, true, 0.2/sqrt(2)), 0.0f,
    D2V(pt1, false, 0.2/sqrt(2)), D2V(pt1, true, 0.2/sqrt(2)), 0.0f,
    D2V(pt4, false, 0.2/sqrt(2)), D2V(pt4, true, 0.2/sqrt(2)), 0.0f,
    D2V(pt3, false, 0.2/sqrt(2)), D2V(pt3, true, 0.2/sqrt(2)), 0.0f,
  };

  float colors[] = {
    0.5f, 1.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.5f,
    0.0f, 1.0f, 1.0f,

    229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f, 
    229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f, 
    229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f, 
    229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f, 
    229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f
  };


  unsigned int buffer, vArray;
  glGenVertexArrays(1, &vArray);
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), 0, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), &colors);

  glBindVertexArray(vArray);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(vertices)));
  glEnableVertexAttribArray(1);


  Shaders shaders("src/shaders/shaders.vs", "src/shaders/shaders.fs");


  while (!glfwWindowShouldClose(window)) {
    glfwSetKeyCallback(window, key_callback);

    glClearColor(229.0f/255.0f, 159.0f/255.0f, 246.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaders.shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 2, 3);
    glDrawArrays(GL_TRIANGLES, 5, 3);
    glDrawArrays(GL_TRIANGLES, 7, 3);

    Increment(pt1);
    Increment(pt2);
    Increment(pt3);
    Increment(pt4);

    float newVertices[] = {
      D2V(pt2, false, 1/sqrt(2)), D2V(pt2, true, 1/sqrt(2)), 0.0f,
      D2V(pt3, false, 1/sqrt(2)), D2V(pt3, true, 1/sqrt(2)), 0.0f,
      D2V(pt1, false, 1/sqrt(2)), D2V(pt1, true, 1/sqrt(2)), 0.0f,
      D2V(pt4, false, 1/sqrt(2)), D2V(pt4, true, 1/sqrt(2)), 0.0f,
      D2V(pt3, false, 1/sqrt(2)), D2V(pt3, true, 1/sqrt(2)), 0.0f,

      D2V(pt2, false, 0.2/sqrt(2)), D2V(pt2, true, 0.2/sqrt(2)), 0.0f,
      D2V(pt3, false, 0.2/sqrt(2)), D2V(pt3, true, 0.2/sqrt(2)), 0.0f,
      D2V(pt1, false, 0.2/sqrt(2)), D2V(pt1, true, 0.2/sqrt(2)), 0.0f,
      D2V(pt4, false, 0.2/sqrt(2)), D2V(pt4, true, 0.2/sqrt(2)), 0.0f,
      D2V(pt3, false, 0.2/sqrt(2)), D2V(pt3, true, 0.2/sqrt(2)), 0.0f,
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newVertices), &newVertices);
    glfwSwapBuffers(window);

    glfwPollEvents();

//    std::cout << pt1 << "\n" << pt2 << "\n"<< pt3 << "\n"<< pt4 << "\n" << std::endl;
  }


  glfwTerminate();
  return 0;
}
