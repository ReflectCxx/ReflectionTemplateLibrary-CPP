# CMakeLists.txt for CxxReflectionTemplates

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(CxxReflectionTemplates)

SET(CXX_LIB_NAME CxxReflectionTemplates)

ADD_LIBRARY(${PROJECT_NAME} STATIC "")

INCLUDE_DIRECTORIES(inc)

# Add the source directory
INCLUDE(src/CMakeLists.txt)