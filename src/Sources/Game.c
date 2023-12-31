#include "../Headers/Game.h"

extern const unsigned int WINDOW_WIDTH;
extern const unsigned int WINDOW_HEIGHT;

extern Camera mainCamera;

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

  GLclampf red   = 0.78f;
  GLclampf green = 0.72f;
  GLclampf blue  = 0.55f;
  GLclampf alpha = 1.0f;
  glClearColor(red, green, blue, alpha);

  // Point Size

  glPointSize(5.f);

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

void dp_handleInputs(GLFWwindow* window, float deltaTime, bool* cameraLocked)
{
  // Locking the Camera

  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
  {
    *cameraLocked = true;
    glfwSetCursorPos(window, (double)WINDOW_WIDTH / 2, (double)WINDOW_HEIGHT / 2);
    return;
  }
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    *cameraLocked = false;
  }

  // Updating the Cursor

  if (!*cameraLocked) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    return;
  }

  // Polygon Modes

  if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  }
  if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    vec3 finalVector;
    glm_vec3_scale(mainCamera.front, mainCamera.speed * deltaTime, finalVector);
    glm_vec3_add(mainCamera.position, finalVector, mainCamera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    vec3 finalVector;
  
    glm_vec3_cross(mainCamera.front, mainCamera.up, finalVector);
    glm_vec3_normalize(finalVector);
    glm_vec3_scale(finalVector, mainCamera.speed * deltaTime, finalVector);

    glm_vec3_sub(mainCamera.position, finalVector, mainCamera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    vec3 finalVector;
    glm_vec3_scale(mainCamera.front, mainCamera.speed * deltaTime, finalVector);
    glm_vec3_sub(mainCamera.position, finalVector, mainCamera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    vec3 finalVector;
  
    glm_vec3_cross(mainCamera.front, mainCamera.up, finalVector);
    glm_vec3_normalize(finalVector);
    glm_vec3_scale(finalVector, mainCamera.speed * deltaTime, finalVector);
  
    glm_vec3_add(mainCamera.position, finalVector, mainCamera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    glm_vec3_add(mainCamera.position, (vec3){ 0.f, 1.f * deltaTime * mainCamera.speed, 0.f }, mainCamera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
  {
    glm_vec3_add(mainCamera.position, (vec3){ 0.f, -1.f * deltaTime * mainCamera.speed, 0.f }, mainCamera.position);
  }

  // Mouse Movement

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  double mouseX;
  double mouseY;
  glfwGetCursorPos(window, &mouseX, &mouseY);

  float deltaX = (float)mouseX - ((float)WINDOW_WIDTH / 2);
  float deltaY = ((float)WINDOW_HEIGHT / 2) - (float)mouseY;

  mainCamera.yaw += deltaX * mainCamera.sensitivity * deltaTime;
  mainCamera.pitch += deltaY * mainCamera.sensitivity * deltaTime;

  if (mainCamera.pitch > 89.f) mainCamera.pitch = 89.f;
  if (mainCamera.pitch < -89.f) mainCamera.pitch = -89.f;

  dp_updateFront(&mainCamera);
  glfwSetCursorPos(window, (double)WINDOW_WIDTH / 2, (double)WINDOW_HEIGHT / 2);
}
