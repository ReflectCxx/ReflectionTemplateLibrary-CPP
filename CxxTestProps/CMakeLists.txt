# CMakeLists.txt for CxxTestProps

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(CxxTestProps)

set(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY(${PROJECT_NAME} STATIC "")

INCLUDE_DIRECTORIES(inc)

# Add the source directory
INCLUDE(src/CMakeLists.txt)