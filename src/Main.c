#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdlib.h>
#include <stdio.h>

#include "Headers/Game.h"
#include "Headers/Graphics.h"
#include "Headers/Camera.h"

#include "Utils/Image.h"

// Constants

const unsigned int WINDOW_WIDTH       = 800;
const unsigned int WINDOW_HEIGHT      = 600;
const char*        WINDOW_TITLE       = "GLFW";

// Vertices and Indices

GLfloat vertices[] = {
  -0.5f, -0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.5f, -0.5f,  0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
  -0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f, 1.f, 1.f,
   0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.5f, -0.5f,  0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.5f,  0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f,
   0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f,
  -0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.5f,  0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f,
  -0.5f,  0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f,
  -0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f,
  -0.5f, -0.5f,  0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
  -0.5f,  0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f,
  -0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 1.f,
  -0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f,
   0.5f,  0.5f,  0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
  -0.5f,  0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f,
   0.5f,  0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f,
   0.5f, -0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f,
  -0.5f, -0.5f,  0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
   0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f,
  -0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f,
};
GLuint indices[] = {
  0, 1, 3,     // Front
  3, 2, 0,     // Front
  4, 5, 7,     // Right
  7, 6, 4,     // Right
  8, 9, 11,    // Back
  11, 10, 8,   // Back
  12, 13, 15,  // Left
  15, 14, 12,  // Left
  16, 17, 19,  // Top
  19, 18, 16,  // Top
  20, 21, 23,  // Bottom
  23, 22, 20,  // Bottom
};

// Callbacks

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Camera

Camera mainCamera = {
  .position = (vec3){ 0.f, 0.f, 3.f },
  .front = (vec3){ 0.f, 0.f, -1.f },
  .up = (vec3){ 0.f, 1.f, 0.f },
  .yaw = 270.f,
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

  dp_linkAttrib(&VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  dp_linkAttrib(&VBO1, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  dp_linkAttrib(&VBO1, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

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

  // Textures
  
  Texture grassTexture;
  dp_initTexture(&grassTexture, "assets/Textures/grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

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
    dp_bindTexture(&grassTexture);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(window);
  }

  // Terminating the Program

  dp_deleteVAO(&VAO1);
  dp_deleteVBO(&VBO1);
  dp_deleteEBO(&EBO1);
  dp_deleteShader(&defaultShader);
  dp_deleteTexture(&grassTexture);
  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}

// Callbacks

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
