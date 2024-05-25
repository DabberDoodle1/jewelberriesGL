#include "../include/world.hpp"

World::World(const char* ptitle, int width, int height) {

  title = ptitle;
  WINDOW_WIDTH = width;
  WINDOW_HEIGHT = height;

}

void World::Start() {
  

  if (!glfwInit()) {
    std::cout << "ERROR: GLFW not INITIALIZED!\n" << std::endl;
    return;
  }


  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);

  if (!window) {
    std::cout << "ERROR: WINDOW not INITIALIZED!\n" << std::endl;
    End();
    return;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {
    glViewport(0, 0, width, height);
  });


  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "ERROR: GLAD not INITIALIZED!\n" << std::endl;
    return;
  }
}

void World::End() {
  glfwTerminate();
}

void World::FillBackground(int r, int g, int b) {
  glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
