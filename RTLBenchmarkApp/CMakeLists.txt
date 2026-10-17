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
    src/StdFunction.cpp
    src/ReflectedCallKnownReturn.h
    src/ReflectedCallKnownReturn.cpp
    src/ReflectedCallUnknownReturn.h
    src/ReflectedCallUnknownReturn.cpp
)


target_link_libraries(${CXX_EXE_NAME}
    PRIVATE
        benchmark
        ReflectionTemplateLib
)