#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "Headers/Graphics.h"

// Constants
const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "GLFW";

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

// Shader Source Codes
const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aCol;\n"
  "out vec3 vertCol;\n"
  "void main()\n"
  "{\n"
  "  gl_Position = vec4(aPos, 1.f);\n"
  "  vertCol = aCol;\n"
  "}\0";
const char* fragmentShaderSource =
  "#version 330 core\n"
  "in vec3 vertCol;\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "  FragColor = vec4(vertCol, 1.f);\n"
  "}\0";

// Callbacks
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main()
{
  // Initializing GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Creating the Window
  GLFWwindow* window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE,
    NULL,
    NULL
  );
  if (window == NULL)
  {
    printf("Failed to create a GLFW window!\n");
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  // Initializing GLEW
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    printf("Failed to initialize GLEW!\n");
    printf("Error: %s\n", glewGetErrorString(err));
    glfwTerminate();
    return EXIT_FAILURE;
  }
  printf("GLEW: %s\n", glewGetString(GLEW_VERSION));

  // Clear Color
  GLclampf red   = 0.0f;
  GLclampf green = 0.3f;
  GLclampf blue  = 0.3f;
  GLclampf alpha = 1.0f;
  glClearColor(red, green, blue, alpha);

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

  // Info Log
  int success;
  char infoLog[512];

  // Shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // Validating Vertex Shader
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("Failed to compile the vertex shader!\n");
    printf("Error: %s\n", infoLog);
  }

  // Validating Fragment Shader
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("Failed to compile the fragment shader!\n");
    printf("Error: %s\n", infoLog);
  }

  // Shader Program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Validating Shader Program
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("Failed to link the shader program!\n");
    printf("Error: %s\n", infoLog);
  }

  // Deleting the Shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Callbacks
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    dp_bindVAO(&VAO1);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(window);
  }

  // Terminating the Program
  dp_deleteVAO(&VAO1);
  dp_deleteVBO(&VBO1);
  dp_deleteEBO(&EBO1);
  glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}

// Callbacks
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
