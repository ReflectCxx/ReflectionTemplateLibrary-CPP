# CMakeLists.txt for the entire project
cmake_minimum_required(VERSION 3.20)
# Set the project name
project(CxxReflectionProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Add the subdirectories
add_subdirectory(CxxTestDesignPatternsUsingRTL)
add_subdirectory(CxxRTLTypeRegistration)
add_subdirectory(CxxRTLTestApplication)
add_subdirectory(CxxTestProject)
add_subdirectory(CxxTestUtils)
add_subdirectory(ReflectionTemplateLib)