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
const float        CAMERA_FOV         = 40.f;
const float        CAMERA_NEAR        = 0.1f;
const float        CAMERA_FAR         = 100.f;
const float        CAMERA_SPEED       = 2.f;
const float        CAMERA_SENSITIVITY = 3.f;

// Vertices and Indices

GLfloat vertices[] = {
  -0.5f,  -0.5f,  0.5f,  0.2f, 0.2f, 0.2f,
   0.0f,  -0.5f,  0.5f,  0.2f, 0.2f, 0.2f,
   0.5f,  -0.5f,  0.5f,  0.2f, 0.2f, 0.2f,
  -0.5f,  -0.5f,  0.0f,  0.2f, 0.2f, 0.2f,
   0.0f,  -0.5f,  0.0f,  0.2f, 0.2f, 0.2f,
   0.5f,  -0.5f,  0.0f,  0.2f, 0.2f, 0.2f,
  -0.5f,  -0.5f, -0.5f,  0.2f, 0.2f, 0.2f,
   0.0f,  -0.5f, -0.5f,  0.2f, 0.2f, 0.2f,
   0.5f,  -0.5f, -0.5f,  0.2f, 0.2f, 0.2f,
  -0.25f,  0.0f,  0.25f, 0.2f, 0.2f, 0.2f,
   0.25f,  0.0f,  0.25f, 0.2f, 0.2f, 0.2f,
  -0.25f,  0.0f, -0.25f, 0.2f, 0.2f, 0.2f,
   0.25f,  0.0f, -0.25f, 0.2f, 0.2f, 0.2f,
   0.0f,   0.5f,  0.0f,  0.2f, 0.2f, 0.2f,
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
  vec3 front;
  front[0] = cos(glm_rad(mainCamera.yaw)) * cos(glm_rad(mainCamera.pitch));
  front[1] = sin(glm_rad(mainCamera.pitch));
  front[2] = sin(glm_rad(mainCamera.yaw)) * cos(glm_rad(mainCamera.pitch));
  glm_vec3_copy(front, mainCamera.front);
  glm_vec3_normalize(mainCamera.front);

  // Main Loop

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    dt_updateDeltaTime(&deltaTime, &previousTime);
    dp_handleInputs(window, deltaTime, &cameraLocked);

    GLuint modelLoc = glGetUniformLocation(defaultShader.ID, "model");
    GLuint viewLoc = glGetUniformLocation(defaultShader.ID, "view");
    GLuint projectionLoc = glGetUniformLocation(defaultShader.ID, "projection");

    // Matrices

    mat4 model;
    mat4 view;
    mat4 projection;

    glm_mat4_identity(model);
    glm_mat4_identity(view);
    glm_mat4_identity(projection);

    vec3 aaa;
    glm_vec3_add(mainCamera.position, mainCamera.front, aaa);

    glm_perspective(glm_rad(CAMERA_FOV), (float)WINDOW_WIDTH / WINDOW_HEIGHT, CAMERA_NEAR, CAMERA_FAR, projection);
    glm_lookat(mainCamera.position, aaa, mainCamera.up, view);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat*)view);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (GLfloat*)projection);

    dp_useShader(&defaultShader);
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
