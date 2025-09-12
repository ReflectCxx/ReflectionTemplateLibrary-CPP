# CMakeLists.txt for the entire project
cmake_minimum_required(VERSION 3.20)
# Set the project name
project(CxxReflectionProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Add the subdirectories
add_subdirectory(CxxTestRegistration)
add_subdirectory(RTLTestRunApp)
add_subdirectory(RTLBenchmarkApp)
add_subdirectory(CxxTestProps)
add_subdirectory(CxxTestUtils)
add_subdirectory(ReflectionTemplateLib)