cmake_minimum_required(VERSION 3.20)
project(CxxRTLTestApplication LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===============================
# Dependencies (GoogleTest)
# ===============================
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Prevent GTest from overriding CRT settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Avoid GTest adding its own tests into the solution
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ===============================
# Common Include Paths
# ===============================
set(RTL_INCLUDE_DIRS
    inc
    "${CMAKE_SOURCE_DIR}/CxxTestUtils/inc"
    "${CMAKE_SOURCE_DIR}/CxxRTLTypeRegistration/inc"
    "${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/common"
    "${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/detail/inc"
    "${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/access/inc"
    "${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/builder/inc"
)

# ===============================
# Test Executable
# ===============================
set(CXX_EXE_NAME CxxRTLTestApplication)

# Add all test sources (either glob or include your src/CMakeLists.txt)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${CXX_EXE_NAME} ${TEST_SOURCES})

target_include_directories(${CXX_EXE_NAME} PRIVATE ${RTL_INCLUDE_DIRS})

target_link_libraries(${CXX_EXE_NAME}
    PRIVATE
        CxxTestUtils
        ReflectionTemplateLib
        CxxRTLTypeRegistration
        GTest::gtest_main
)

# ===============================
# GoogleTest Integration
# ===============================
include(GoogleTest)
gtest_discover_tests(${CXX_EXE_NAME})
