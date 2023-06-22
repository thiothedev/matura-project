#include "../Headers/Graphics.h"

void dp_initVAO(VAO* VAO)
{
  glGenVertexArrays(1, &VAO->ID);
}

void dp_bindVAO(VAO* VAO)
{
  glBindVertexArray(VAO->ID);
}

void dp_linkAttrib(VBO* VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset)
{
  glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
}

void dp_unbindVAO()
{
  glBindVertexArray(0);
}

void dp_deleteVAO(VAO* VAO)
{
  glDeleteBuffers(1, &VAO->ID);
}

void dp_initVBO(VBO* VBO, GLfloat vertices[], GLsizeiptr size)
{
  glGenBuffers(1, &VBO->ID);
  glBindBuffer(GL_ARRAY_BUFFER, VBO->ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void dp_bindVBO(VBO* VBO)
{
  glBindBuffer(GL_ARRAY_BUFFER, VBO->ID);
}

void dp_unbindVBO()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void dp_deleteVBO(VBO* VBO)
{
  glDeleteBuffers(1, &VBO->ID);
}

void dp_initEBO(EBO* EBO, GLuint indices[], GLsizeiptr size)
{
  glGenBuffers(1, &EBO->ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO->ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void dp_bindEBO(EBO* EBO)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO->ID);
}

void dp_unbindEBO()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void dp_deleteEBO(EBO* EBO)
{
  glDeleteBuffers(1, &EBO->ID);
}

void dp_initShader(Shader* Shader, const char* vertexSourcePath, const char* fragmentSourcePath)
{
  // Info Log
  int success;
  char infoLog[512];

  // Shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  const char* vertexShaderSource = dp_file_getContents(vertexSourcePath);
  const char* fragmentShaderSource = dp_file_getContents(fragmentSourcePath);

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
  Shader->ID = glCreateProgram();
  glAttachShader(Shader->ID, vertexShader);
  glAttachShader(Shader->ID, fragmentShader);
  glLinkProgram(Shader->ID);

  // Validating Shader Program
  glGetProgramiv(Shader->ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(Shader->ID, 512, NULL, infoLog);
    printf("Failed to link the shader program!\n");
    printf("Error: %s\n", infoLog);
  }

  // Deleting the Shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void dp_useShader(Shader* Shader)
{
  glUseProgram(Shader->ID);
}

void dp_deleteShader(Shader* Shader)
{
  glDeleteProgram(Shader->ID);
}

void dp_initTexture(Texture* texture, const char* path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
  texture->type = texType;

  int width;
  int height;
  char* data;
  dp_image_loadFromPng(path, &data, &width, &height);

  glGenTextures(1, &texture->ID);
  glActiveTexture(slot);
	glBindTexture(texType, texture->ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixelType, data);
	glGenerateMipmap(texType);

  free(data);
  glBindTexture(texType, 0);
}

void dp_textureUnit(Shader* shader, const char* uniform, GLuint unit)
{
  GLuint textureLoc = glGetUniformLocation(shader->ID, uniform);
  dp_useShader(shader);
  glUniform1i(textureLoc, unit);
}

void dp_bindTexture(Texture* texture)
{
  glBindTexture(texture->type, texture->ID);
}

void dp_unbindTexture(Texture* texture)
{
  glBindTexture(texture->type, 0);
}

void dp_deleteTexture(Texture* texture)
{
  glDeleteTextures(1, &texture->ID);
}
