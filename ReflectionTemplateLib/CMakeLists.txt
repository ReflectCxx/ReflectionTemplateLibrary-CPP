# CMakeLists.txt for ReflectionTemplateLib

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(ReflectionTemplateLib)

set(CMAKE_CXX_STANDARD 20)

SET(CXX_LIB_NAME ReflectionTemplateLib)

ADD_LIBRARY(${PROJECT_NAME} STATIC "")

INCLUDE_DIRECTORIES(common)
INCLUDE_DIRECTORIES(detail/inc)
INCLUDE_DIRECTORIES(access/inc)
INCLUDE_DIRECTORIES(builder/inc)

# Add the source directory
INCLUDE(detail/src/CMakeLists.txt)
INCLUDE(access/src/CMakeLists.txt)
INCLUDE(builder/src/CMakeLists.txt)