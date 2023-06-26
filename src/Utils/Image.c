#include "Image.h"

const bool dp_image_loadFromPng(const char* path, char** data, int* width, int* height)
{
  png_image image;
  memset(&image, 0, sizeof(image));
  image.version = PNG_IMAGE_VERSION;

  if (!png_image_begin_read_from_file(&image, path))
  {
    printf("Failed to begin reading PNG: %s!\n", path);
    return false;
  }

  image.format = PNG_FORMAT_RGBA;
  *data = (char*)malloc(PNG_IMAGE_SIZE(image));

  if (!png_image_finish_read(&image, NULL, *data, 0, NULL))
  {
    printf("Failed to finish reading PNG: %s!\n", path);
    free(*data);
    return false;
  }

  size_t rowSize = PNG_IMAGE_ROW_STRIDE(image);
  char* tempRow = (char*)malloc(rowSize);

  for (int y = 0; y < image.height / 2; ++y)
  {
    char* row1 = *data + y * rowSize;
    char* row2 = *data + (image.height - y - 1) * rowSize;

    memcpy(tempRow, row1, rowSize);
    memcpy(row1, row2, rowSize);
    memcpy(row2, tempRow, rowSize);
  }

  free(tempRow);

  *width = image.width;
  *height = image.height;

  return true;
}
