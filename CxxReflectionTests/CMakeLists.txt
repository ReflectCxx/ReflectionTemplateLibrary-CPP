# CMakeLists.txt for CxxReflectionTests
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(CxxReflectionTests)

SET(CXX_EXE_NAME CxxReflectionTests)
ADD_EXECUTABLE(${CXX_EXE_NAME} "")

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/CxxTypeRegistration/inc")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/common")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/access/inc")

TARGET_LINK_LIBRARIES(${CXX_EXE_NAME} CxxTypeRegistration)
TARGET_LINK_LIBRARIES(${CXX_EXE_NAME} ReflectionTemplateLib)

# Add the source directory
INCLUDE(src/CMakeLists.txt)