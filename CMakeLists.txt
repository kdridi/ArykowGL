cmake_minimum_required(VERSION 2.8.9)

project(Arykow)
set (PKG_CONFIG_EXECUTABLE /usr/local/bin/pkg-config)
set (EXECUTABLE_OUTPUT_PATH bin/)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)
find_package (Boost REQUIRED)

find_package(PkgConfig)
pkg_check_modules (GLEW glew>=1.8.0)

include_directories (
  ${OPENGL_INCLUDE_DIR}
  ${GLUT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  )

link_directories (
  ${Boost_LIBRARY_DIRS}
  ${GLEW_LIBRARY_DIRS}
  )

file(
  GLOB_RECURSE
  source_files
  ./src/*
  )

add_executable (
  Arykow
  ${source_files}
  )

target_link_libraries (
  Arykow
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARIES}
  ${GLEW_LIBRARIES}
  )
