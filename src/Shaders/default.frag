#version 330 core

in vec3 vertCol;
in vec2 vertTex;
in vec3 vertNorm;
in vec3 vertPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightCol;
uniform vec3 camPos;

uniform sampler2D myTexture;

void main()
{
  float ambient = 0.1f;

  vec3 normal = normalize(vertNorm);
  vec3 lightDirection = normalize(lightPos - vertPos);
  float diffuse = max(dot(normal, lightDirection), 0.f);

  float specularStrength = 0.5f;
  vec3 viewDirection = normalize(camPos - vertPos);
  vec3 reflectionDirection = reflect(-viewDirection, normal);
  float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.f), 8);
  float specular = specAmount * specularStrength;

  FragColor = texture(myTexture, vertTex) * vec4(lightCol, 1.f) * (ambient + diffuse + specular);
}
