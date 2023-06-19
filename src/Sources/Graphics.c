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
