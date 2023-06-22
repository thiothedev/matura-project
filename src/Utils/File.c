#include "File.h"

const char* dp_file_getContents(const char* path)
{
  FILE* file = fopen(path, "rb");
  if (file == NULL) {
      fprintf(stderr, "Failed to read file %s!\n", path);
      return NULL;
  }

  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* buffer = (char*)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Memory allocation error!\n");
    fclose(file);
    return NULL;
  }

  size_t readSize = fread(buffer, 1, fileSize, file);
  fclose(file);

  if (readSize != fileSize) {
    fprintf(stderr, "Error reading file %s!\n", path);
    free(buffer);
    return NULL;
  }

  buffer[fileSize] = '\0';
  return buffer;
}
