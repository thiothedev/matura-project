#include "../Headers/Game.h"

bool dp_initializeGlfw()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
}

GLFWwindow* dp_initializeWindow(const unsigned int width, const unsigned int height, const char* title)
{
   GLFWwindow* window = glfwCreateWindow(
    width,
    height,
    title,
    NULL,
    NULL
  );
  if (window == NULL)
  {
    printf("Failed to create a GLFW window!\n");
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);
  return window;
}

bool dp_initializeGlew()
{
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    printf("Failed to initialize GLEW!\n");
    printf("Error: %s\n", glewGetErrorString(err));
    glfwTerminate();
    return false;
  }
  printf("GLEW: %s\n", glewGetString(GLEW_VERSION));
  return true;
}
