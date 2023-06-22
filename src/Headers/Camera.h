#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

typedef struct Camera
{
  vec3 position;
  vec3 front;
  vec3 up;
  float pitch;
  float yaw;
} Camera;

#endif // CAMERA_H
