#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool dp_initializeGlfw();
GLFWwindow* dp_initializeWindow(const unsigned int width, const unsigned int height, const char* title);
bool dp_initializeGlew();

#endif // GAME_H
