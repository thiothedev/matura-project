#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glew.h>

typedef struct VAO
{
  GLuint ID;
} VAO;

typedef struct VBO
{
  GLuint ID;
} VBO;

typedef struct EBO
{
  GLuint ID;
} EBO;

void dp_initVAO(VAO* VAO);
void dp_bindVAO(VAO* VAO);
void dp_linkAttrib(VBO* VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset);
void dp_unbindVAO();
void dp_deleteVAO(VAO* VAO);

void dp_initVBO(VBO* VBO, GLfloat vertices[], GLsizeiptr size);
void dp_bindVBO(VBO* VBO);
void dp_unbindVBO();
void dp_deleteVBO(VBO* VBO);

void dp_initEBO(EBO* EBO, GLuint indices[], GLsizeiptr size);
void dp_bindEBO(EBO* EBO);
void dp_unbindEBO();
void dp_deleteEBO(EBO* EBO);

#endif // GRAPHICS_H
