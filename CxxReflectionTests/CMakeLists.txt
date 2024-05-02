# CMakeLists.txt for CxxReflectionTests
cmake_minimum_required(VERSION 3.20)

SET(CXX_EXE_NAME CxxReflectionTests)
ADD_EXECUTABLE(${CXX_EXE_NAME} "")

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/CxxReflectionTemplates/inc")

TARGET_LINK_LIBRARIES(${CXX_EXE_NAME} CxxReflectionTemplates)

# Add the source directory
INCLUDE(src/CMakeLists.txt)
