# CMakeLists.txt for SingletonReflectedAccess

# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(ReflectionTemplateLibUnitTests)

set(CMAKE_CXX_STANDARD 20)

# Set the build type to Debug
#set(CMAKE_BUILD_TYPE Debug)

# Enable debug symbols
#set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(CXX_EXE_NAME ReflectionTemplateLibUnitTests)
add_executable(${CXX_EXE_NAME} "")


INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/common")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/detail/inc")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/access/inc")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/builder/inc")

target_link_libraries(${CXX_EXE_NAME} ReflectionTemplateLib)
target_link_libraries(${CXX_EXE_NAME} GTest::gtest_main)

# Add the source directory
INCLUDE(src/CMakeLists.txt)

include(GoogleTest)
gtest_discover_tests(${CXX_EXE_NAME})