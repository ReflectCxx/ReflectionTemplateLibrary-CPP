# CMakeLists.txt for CxxTypeRegistration

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(CxxTypeRegistration)

set(CMAKE_CXX_STANDARD 20)

SET(CXX_LIB_NAME CxxTypeRegistration)

ADD_LIBRARY(${PROJECT_NAME} STATIC "")

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/CxxTestProject/inc")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/common")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/detail/inc")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/access/inc")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/builder/inc")

#TARGET_LINK_LIBRARIES(${CXX_EXE_NAME} CxxTestProject)
TARGET_LINK_LIBRARIES(${CXX_EXE_NAME} ReflectionTemplateLib)

# Add the source directory
INCLUDE(src/CMakeLists.txt)