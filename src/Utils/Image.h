#ifndef IMAGE_H
#define IMAGE_H

#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Loads an image from a PNG file and returns the image data as a pointer to a character array.
 * @param path The path to the PNG file.
 * @return A pointer to a character array containing the image data, or NULL if an error occurs.
*/
const bool dp_image_loadFromPng(const char* path, char** data, int* width, int* height);

#endif // IMAGE_H
