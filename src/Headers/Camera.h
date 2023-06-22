#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <cglm/cglm.h>

#include "Graphics.h"

/**
 * Represents a camera used for rendering scenes.
 */
typedef struct Camera
{
  vec3 position;
  vec3 front;
  vec3 up;
  float pitch;
  float yaw;
  float fov;
  float aspect;
  float near;
  float far;
  float speed;
  float sensitivity;
} Camera;

/**
 * Updates the Model-View-Projection (MVP) matrices using the information from the specified Camera object
 * and applies them to the specified Shader object.
 *
 * @param camera The Camera object from which the position and other information will be used to update the matrices.
 * @param shader The Shader object to which the updated matrices will be applied.
 */
void dp_updateMatrices(Camera* camera, Shader* shader);
/**
 * Updates the front vector of the camera based on the pitch and yaw angles.
 * This function recalculates the front vector to reflect the new orientation
 * of the camera.
 *
 * @param camera The Camera struct representing the camera.
 */
void dp_updateFront(Camera* camera);

#endif // CAMERA_H
