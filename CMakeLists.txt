cmake_minimum_required(VERSION 2.8.9)
 
project(Cube3D)
set (EXECUTABLE_OUTPUT_PATH bin/)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
 
find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)
find_package (Boost REQUIRED)

include_directories (
  /usr/local/include
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  ${BOOST_INCLUDE_DIR}
)
 
file(
  GLOB_RECURSE
  source_files
  ./src/*
)
 
add_executable (
  Cube3D
  ${source_files}
)
 
target_link_libraries (
  Cube3D
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY}
  ${BOOST_LIBRARY}
)