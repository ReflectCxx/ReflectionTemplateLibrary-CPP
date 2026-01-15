cmake_minimum_required(VERSION 3.20)
project(CxxReflectionProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# ----------------------------
# Coverage Support (Linux)
# ----------------------------
option(ENABLE_COVERAGE "Enable code coverage" OFF)

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Code coverage enabled")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# ----------------------------
# Subdirectories
# ----------------------------
add_subdirectory(ReflectionTemplateLib)
add_subdirectory(CxxTestRegistration)
add_subdirectory(CxxTestProps)
add_subdirectory(CxxTestUtils)
add_subdirectory(RTLTestRunApp)
add_subdirectory(RTLBenchmarkApp)
add_subdirectory(demo)
