#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdlib.h>
#include <stdio.h>

#include "Headers/Game.h"
#include "Headers/Graphics.h"
#include "Headers/Camera.h"

// Constants

const unsigned int WINDOW_WIDTH       = 800;
const unsigned int WINDOW_HEIGHT      = 600;
const char*        WINDOW_TITLE       = "GLFW";

// Vertices and Indices

GLfloat vertices[] = {
  -0.5f,  -0.5f,  0.5f,  0.2f, 0.2f, 0.2f,
   0.0f,  -0.5f,  0.5f,  0.1f, 0.1f, 0.1f,
   0.5f,  -0.5f,  0.5f,  0.2f, 0.2f, 0.2f,
  -0.5f,  -0.5f,  0.0f,  0.1f, 0.1f, 0.1f,
   0.0f,  -0.5f,  0.0f,  0.2f, 0.2f, 0.2f,
   0.5f,  -0.5f,  0.0f,  0.1f, 0.1f, 0.1f,
  -0.5f,  -0.5f, -0.5f,  0.2f, 0.2f, 0.2f,
   0.0f,  -0.5f, -0.5f,  0.1f, 0.1f, 0.1f,
   0.5f,  -0.5f, -0.5f,  0.2f, 0.2f, 0.2f,
  -0.25f,  0.0f,  0.25f, 0.1f, 0.1f, 0.1f,
   0.25f,  0.0f,  0.25f, 0.2f, 0.2f, 0.2f,
  -0.25f,  0.0f, -0.25f, 0.1f, 0.1f, 0.1f,
   0.25f,  0.0f, -0.25f, 0.2f, 0.2f, 0.2f,
   0.0f,   0.5f,  0.0f,  0.1f, 0.1f, 0.1f,
};
GLuint indices[] = {
  0, 1, 4,    // Front Left - BT
  4, 3, 0,    // Front Left - BT
  0, 1, 9,    // Front Left - F
  4, 3, 9,    // Front Left - B,
  3, 0, 9,    // Front Left - L,
  1, 4, 9,    // Front Left - R,
  1, 2, 5,    // Front Right - BT
  5, 4, 1,    // Front Right - BT
  1, 2, 10,   // Front Right - F
  5, 4, 10,   // Front Right - B
  4, 1, 10,   // Front Right - L,
  2, 5, 10,   // Front Right - R,
  3, 4, 7,    // Back Left - BT
  7, 6, 3,    // Back Left - BT
  3, 4, 11,   // Back Left - F
  7, 6, 11,   // Back Left - B
  6, 3, 11,   // Back Left - L,
  4, 7, 11,   // Back Left - R,
  4, 5, 8,    // Back Right - BT
  8, 7, 4,    // Back Right - BT
  4, 5, 12,   // Back Right - F
  8, 7, 12,   // Back Right - B
  7, 4, 12,   // Back Right - L,
  5, 8, 12,   // Back Right - R,
  9, 10, 12,  // Top - BT
  12, 11, 9,  // Top - BT
  9, 10, 13,  // Top - F
  12, 11, 13, // Top - B
  11, 9, 13,  // Top - L
  10, 12, 13, // Top - R
};

// Callbacks

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Camera

Camera mainCamera = {
  .position = (vec3){ 0.f, 0.f, -3.f },
  .front = (vec3){ 0.f, 0.f, -1.f },
  .up = (vec3){ 0.f, 1.f, 0.f },
  .yaw = 90.f,
  .pitch = 0.f,
  .fov = 70.f,
  .aspect = (float)WINDOW_WIDTH / WINDOW_HEIGHT,
  .near = 0.1f,
  .far = 100.f,
  .speed = 2.f,
  .sensitivity = 3.f,
};

int main()
{
  // Window

  GLFWwindow* window = NULL;

  // Initializing

  dp_initializeGlfw();
  dp_initializeWindow(&window, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  dp_initializeGlew();

  // VAO, VBO, and EBO

  VAO VAO1;
  VBO VBO1;
  EBO EBO1;

  dp_initVAO(&VAO1);
  dp_initVBO(&VBO1, vertices, sizeof(vertices));
  dp_initEBO(&EBO1, indices, sizeof(indices));

  dp_bindVAO(&VAO1);
  dp_bindVBO(&VBO1);
  dp_bindEBO(&EBO1);

  dp_linkAttrib(&VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  dp_linkAttrib(&VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  dp_unbindVAO();
  dp_unbindVBO();
  dp_unbindEBO();

  // Shaders

  Shader defaultShader;
  dp_initShader(&defaultShader, "src/Shaders/default.vert", "src/Shaders/default.frag");

  // Callbacks

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Tests

  glEnable(GL_DEPTH_TEST);

  // Delta Time

  float deltaTime = 0.f;
  float previousTime = 0.f;

  // Camera

  vec3 cameraTarget = { 0.f, 0.f, 0.f };
  vec3 cameraDirection;
  bool cameraLocked = false;

  // First Frame Update

  dp_updateFront(&mainCamera);

  // Main Loop

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    dp_useShader(&defaultShader);

    dt_updateDeltaTime(&deltaTime, &previousTime);
    dp_handleInputs(window, deltaTime, &cameraLocked);
    dp_updateMatrices(&mainCamera, &defaultShader);

    dp_bindVAO(&VAO1);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(window);
  }

  // Terminating the Program

  dp_deleteVAO(&VAO1);
  dp_deleteVBO(&VBO1);
  dp_deleteEBO(&EBO1);
  dp_deleteShader(&defaultShader);
  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}

// Callbacks

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
