# CMakeLists.txt for CxxTestUtils

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(CxxTestUtils)

set(CMAKE_CXX_STANDARD 20)

SET(CXX_LIB_NAME CxxTestUtils)

ADD_LIBRARY(${PROJECT_NAME} STATIC "")

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/CxxTestProps/inc")

TARGET_LINK_LIBRARIES(${CXX_LIB_NAME} ReflectionTemplateLib)

# Add the source directory
INCLUDE(src/CMakeLists.txt)