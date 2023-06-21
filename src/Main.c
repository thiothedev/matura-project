#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdlib.h>
#include <stdio.h>

#include "Headers/Game.h"
#include "Headers/Graphics.h"

// Constants

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "GLFW";
const float        CAMERA_FOV    = 45.f;
const float        CAMERA_NEAR   = 0.1f;
const float        CAMERA_FAR    = 100.f;
const float        CAMERA_SPEED  = 2.f;

// Vertices and Indices

GLfloat vertices[] = {
  -0.5f,  -0.5f, 0.f, 1.f, 0.f, 0.f,
   0.0f,  -0.5f, 0.f, 0.f, 1.f, 0.f,
   0.5f,  -0.5f, 0.f, 0.f, 0.f, 1.f,
  -0.25f,  0.0f, 0.f, 1.f, 1.f, 0.f,
   0.25f,  0.0f, 0.f, 0.f, 1.f, 1.f,
   0.0f,   0.5f, 0.f, 1.f, 0.f, 1.f,
};
GLuint indices[] = {
  0, 1, 3,
  1, 2, 4,
  3, 4, 5,
};

// Callbacks

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Position

vec3 position = { 0.f, 0.f, -1.f };

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
  
  // Matrices

  mat4 model;
  mat4 view;
  mat4 projection;

  // Delta Time
  float deltaTime = 0.f;
  float previousTime = 0.f;

  // Main Loop

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    dt_updateDeltaTime(&deltaTime, &previousTime);
    dp_handleInputs(window, deltaTime);

    GLuint modelLoc = glGetUniformLocation(defaultShader.ID, "model");
    GLuint viewLoc = glGetUniformLocation(defaultShader.ID, "view");
    GLuint projectionLoc = glGetUniformLocation(defaultShader.ID, "projection");

    glm_mat4_identity(model);
    glm_mat4_identity(view);
    glm_mat4_identity(projection);

    glm_perspective(glm_rad(CAMERA_FOV), (float)WINDOW_WIDTH / WINDOW_HEIGHT, CAMERA_NEAR, CAMERA_FAR, projection);
    glm_translate(model, position);

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
