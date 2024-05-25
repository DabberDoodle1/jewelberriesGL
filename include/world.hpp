#ifndef WORLD
#define WORLD

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class World {
public:
  World(const char* ptitle, int width, int height);
  void Start();
  void End();
  void FillBackground(int r, int g, int b);
  GLFWwindow* window;
private:
  const char* title;
  GLuint WINDOW_WIDTH, WINDOW_HEIGHT;
};
#endif
