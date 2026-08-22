# CMakeLists.txt for ReflectionTypeRegistration

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(CxxTestRegistration)

set(CMAKE_CXX_STANDARD 20)

SET(CXX_LIB_NAME CxxTestRegistration)

ADD_LIBRARY(${PROJECT_NAME} STATIC "")

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/CxxTestUtils/inc")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/CxxTestProps/inc")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib")

TARGET_LINK_LIBRARIES(${CXX_LIB_NAME} CxxTestProps)
TARGET_LINK_LIBRARIES(${CXX_LIB_NAME} ReflectionTemplateLib)

# Add the source directory
INCLUDE(src/CMakeLists.txt)