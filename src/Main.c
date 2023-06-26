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

const char* ENGINE_NAME    = "Dusky Peak";
const char* ENGINE_VERSION = "0.1";
const char* ENGINE_AUTHOR  = "Robin Patrik Sloup";
const char* ENGINE_LICENSE = "GNU GPLv3";

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "GLFW";

// Vertices and Indices

GLfloat cubeVertices[] = {
   0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f,  1.f, // Front
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  0.f,  1.f, // Front
  -0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f,  1.f, // Front
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  0.f,  1.f, // Front
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  1.f,  0.f,  0.f, // Right
   0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  1.f,  0.f,  0.f, // Right
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  1.f,  0.f,  0.f, // Right
   0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  1.f,  0.f,  0.f, // Right
  -0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f, -1.f, // Back
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  0.f, -1.f, // Back
   0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f, -1.f, // Back
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  0.f, -1.f, // Back
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 1.f, -1.f,  0.f,  0.f, // Left
  -0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, -1.f,  0.f,  0.f, // Left
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 0.f, -1.f,  0.f,  0.f, // Left
  -0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 1.f, -1.f,  0.f,  0.f, // Left
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  1.f,  0.f, // Top
   0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  1.f,  0.f, // Top
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  1.f,  0.f, // Top
  -0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  1.f,  0.f, // Top
  -0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f, -1.f,  0.f, // Bottom
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  0.f, -1.f,  0.f, // Bottom
   0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f, -1.f,  0.f, // Bottom
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  0.f, -1.f,  0.f, // Bottom
};
GLuint cubeIndices[] = {
  0, 1, 3,     // Front
  1, 2, 3,     // Front
  4, 5, 7,     // Right
  5, 6, 7,     // Right
  8, 9, 11,    // Back
  9, 10, 11,   // Back
  12, 13, 15,  // Left
  13, 14, 15,  // Left
  16, 17, 19,  // Top
  17, 18, 19,  // Top
  20, 21, 23,  // Bottom
  21, 22, 23,  // Bottom
};
GLfloat lightVertices[] = {
  -0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f,
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f,
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f,
   0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f,
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f,
   0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f,
  -0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f,
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f,
};
GLuint lightIndices[] = {
  1, 0, 3, // Front
  2, 3, 0, // Front
  5, 1, 7, // Right
  3, 7, 1, // Right
  4, 5, 6, // Back
  7, 6, 5, // Back
  0, 4, 2, // Left
  6, 2, 4, // Left
  2, 3, 7, // Top
  6, 7, 2, // Top
  4, 5, 0, // Bottom
  1, 0, 5, // Bottom
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

  dp_printEngineInfo();
  dp_initializeGlfw();
  dp_initializeWindow(&window, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  dp_initializeGlew();

  // Objects

  VAO cubeVAO;
  VBO cubeVBO;
  EBO cubeEBO;

  dp_initVAO(&cubeVAO);
  dp_initVBO(&cubeVBO, cubeVertices, sizeof(cubeVertices));
  dp_initEBO(&cubeEBO, cubeIndices, sizeof(cubeIndices));

  dp_bindVAO(&cubeVAO);
  dp_bindVBO(&cubeVBO);
  dp_bindEBO(&cubeEBO);

  dp_linkAttrib(&cubeVBO, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)0);
  dp_linkAttrib(&cubeVBO, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  dp_linkAttrib(&cubeVBO, 2, 2, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
  dp_linkAttrib(&cubeVBO, 3, 2, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

  dp_unbindVAO();
  dp_unbindVBO();
  dp_unbindEBO();

  VAO lightVAO;
  VBO lightVBO;
  EBO lightEBO;

  dp_initVAO(&lightVAO);
  dp_initVBO(&lightVBO, lightVertices, sizeof(lightVertices));
  dp_initEBO(&lightEBO, lightIndices, sizeof(lightIndices));

  dp_bindVAO(&lightVAO);
  dp_bindVBO(&lightVBO);
  dp_bindEBO(&lightEBO);

  dp_linkAttrib(&lightVBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  dp_linkAttrib(&lightVBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  dp_unbindVAO();
  dp_unbindVBO();
  dp_unbindEBO();

  // Shaders

  Shader defaultShader;
  dp_initShader(&defaultShader, "src/Shaders/default.vert", "src/Shaders/default.frag");

  Shader lightShader;
  dp_initShader(&lightShader, "src/Shaders/light.vert", "src/Shaders/light.frag");

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
  
  Texture swirlTexture;
  dp_initTexture(&swirlTexture, "assets/Textures/swirl.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

  // Light

   vec3 lightPos = { -3.f, 3.f, 0.f };
   vec3 lightColor = { 1.f, 1.f, 1.f };

  // Main Loop

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    dp_useShader(&defaultShader);
    dp_bindVAO(&cubeVAO);
    dp_bindTexture(&swirlTexture);

    dt_updateDeltaTime(&deltaTime, &previousTime);
    dp_handleInputs(window, deltaTime, &cameraLocked);
    dp_updateMatrices(&mainCamera, &defaultShader);

    mat4 model;
    glm_mat4_identity(model);

    GLuint modelLoc = glGetUniformLocation(defaultShader.ID, "model");
    GLuint lightPosLoc = glGetUniformLocation(defaultShader.ID, "lightPos");
    GLuint lightColLoc = glGetUniformLocation(defaultShader.ID, "lightCol");
    GLuint camPosLoc = glGetUniformLocation(defaultShader.ID, "camPos");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model);
    glUniform3f(lightPosLoc, lightPos[0], lightPos[1], lightColor[2]);
    glUniform3f(lightColLoc, lightColor[0], lightColor[1], lightColor[2]);
    glUniform3f(camPosLoc, mainCamera.position[0], mainCamera.position[1], mainCamera.position[2]);

    glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

    dp_useShader(&lightShader);
    dp_bindVAO(&lightVAO);
    dp_unbindTexture(&swirlTexture);

    glm_translate(model, lightPos);
    dp_updateMatrices(&mainCamera, &lightShader);

    modelLoc = glGetUniformLocation(defaultShader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model);
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

    glfwSwapBuffers(window);
  }

  // Terminating the Program

  dp_deleteVAO(&cubeVAO);
  dp_deleteVBO(&cubeVBO);
  dp_deleteEBO(&cubeEBO);
  dp_deleteVAO(&lightVAO);
  dp_deleteVBO(&lightVBO);
  dp_deleteEBO(&lightEBO);
  dp_deleteShader(&defaultShader);
  dp_deleteShader(&lightShader);
  dp_deleteTexture(&swirlTexture);
  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}

// Callbacks

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
