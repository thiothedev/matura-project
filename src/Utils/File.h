#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Reads the contents of a file and returns them as a character array.
 *
 * @param path The path to the file to be read.
 * @return A character array containing the contents of the file, or null if an error occurs.
 */
const char* dp_file_getContents(const char* path);

#endif // FILE_H
