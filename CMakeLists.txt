# CMake Version
cmake_minimum_required(VERSION 3.3)

# Constants
set(PROJECT_NAME "matura")
set(OpenGL_GL_PREFERENCE LEGACY)

# Options
option(CGLM_USE_C99 "" OFF)

# Project Name
project(${PROJECT_NAME})

# Packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Globs
file(GLOB HEADERS_FILES src/Headers/*.h)
file(GLOB SOURCES_FILES src/Sources/*.c)
file(GLOB UTILS_FILES src/Utils/*.c src/Utils/*.h)

# Executable
add_executable(
  ${PROJECT_NAME}
  src/Main.c
  ${HEADERS_FILES}
  ${SOURCES_FILES}
  ${UTILS_FILES}
)
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PUBLIC GL GLEW glfw)
