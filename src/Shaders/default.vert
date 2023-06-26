#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertCol;
out vec2 vertTex;
out vec3 vertNorm;
out vec3 vertPos;

void main()
{
  vertPos = vec3(model * vec4(aPos, 1.0f));
  gl_Position = projection * view * model * vec4(aPos, 1.f);
  vertCol = aCol;
  vertTex = aTex;
  vertNorm = aNorm;
}
