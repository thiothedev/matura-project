#include "../Headers/Game.h"

bool dp_initializeGlfw()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
}

bool dp_initializeWindow(GLFWwindow** window, const unsigned int width, const unsigned int height, const char* title)
{
  *window = glfwCreateWindow(
    width,
    height,
    title,
    NULL,
    NULL
  );
  if (*window == NULL)
  {
    printf("Failed to create a GLFW window!\n");
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(*window);

  // Clear Color
  GLclampf red   = 0.0f;
  GLclampf green = 0.3f;
  GLclampf blue  = 0.3f;
  GLclampf alpha = 1.0f;
  glClearColor(red, green, blue, alpha);

  return true;
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

void dt_updateDeltaTime(float* deltaTime, float* previousTime)
{
  float currentTime = (float)glfwGetTime();
  *deltaTime = currentTime - *previousTime;
  *previousTime = currentTime;
}

void dp_handleInputs(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS);
}
