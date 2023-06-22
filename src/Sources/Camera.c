#include "../Headers/Camera.h"

void dp_updateMatrices(Camera* camera, Shader* shader)
{
  // Uniform Locations

  GLuint modelLoc = glGetUniformLocation(shader->ID, "model");
  GLuint viewLoc = glGetUniformLocation(shader->ID, "view");
  GLuint projectionLoc = glGetUniformLocation(shader->ID, "projection");

  // Matrices

  mat4 model;
  mat4 view;
  mat4 projection;

  glm_mat4_identity(model);
  glm_mat4_identity(view);
  glm_mat4_identity(projection);

  vec3 targetPosition;
  glm_vec3_add(camera->position, camera->front, targetPosition);

  glm_perspective(glm_rad(camera->fov), camera->aspect, camera->near, camera->far, projection);
  glm_lookat(camera->position, targetPosition, camera->up, view);

  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (GLfloat*)model);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat*)view);
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (GLfloat*)projection);
}

void dp_updateFront(Camera* camera)
{
  vec3 front;
  front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
  front[1] = sin(glm_rad(camera->pitch));
  front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
  glm_vec3_copy(front, camera->front);
  glm_vec3_normalize(camera->front);
}
