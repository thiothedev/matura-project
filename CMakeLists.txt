# CMake Version
cmake_minimum_required(VERSION 3.3)

# Constants
set(PROJECT_NAME "matura")
set(OpenGL_GL_PREFERENCE LEGACY)

# Project Name
project(${PROJECT_NAME})

# Packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Executable
add_executable(
  ${PROJECT_NAME}
  src/Main.c  
)
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PUBLIC GL GLEW glfw)
