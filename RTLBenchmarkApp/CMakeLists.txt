cmake_minimum_required(VERSION 3.20)
project(RTLBenchmarkApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===============================
# Dependencies (Google Benchmark)
# ===============================
include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.3
)

# Prevent benchmark from adding extra projects
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_GetProperties(benchmark)
if(NOT benchmark_POPULATED)
  FetchContent_Populate(benchmark)
  add_subdirectory(${benchmark_SOURCE_DIR} ${benchmark_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ===============================
# Common Include Paths
# ===============================
set(RTL_INCLUDE_DIRS
    inc
    "${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/common"
    "${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/detail/inc"
    "${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/access/inc"
    "${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/builder/inc"
)

# ===============================
# Test Executable
# ===============================
set(CXX_EXE_NAME RTLBenchmarkApp)

# ===============================
# Benchmarks (only target)
# ===============================
add_executable(${CXX_EXE_NAME}
    src/main.cpp
    src/BenchMark.h
    src/BenchMark.cpp
    src/StandardCall.h
    src/StandardCall.cpp
    src/ReflectedCall.h
    src/ReflectedCall.cpp
)


target_include_directories(${CXX_EXE_NAME} PRIVATE ${RTL_INCLUDE_DIRS})

target_link_libraries(${CXX_EXE_NAME}
    PRIVATE
        benchmark
        ReflectionTemplateLib
)