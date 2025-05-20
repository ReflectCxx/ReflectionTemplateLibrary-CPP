# CMakeLists.txt for CxxReflectionTests
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(CxxRTLUseCaseTests)

set(CXX_EXE_NAME CxxRTLUseCaseTests)
add_executable(${CXX_EXE_NAME} "")


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(inc)
include_directories("${CMAKE_SOURCE_DIR}/CxxTestUtils/inc")
include_directories("${CMAKE_SOURCE_DIR}/CxxRTLTypeRegistration/inc")
include_directories("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/common")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/detail/inc")
include_directories("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/access/inc")
include_directories("${CMAKE_SOURCE_DIR}/ReflectionTemplateLib/builder/inc")

target_link_libraries(${CXX_EXE_NAME} CxxTestUtils)
target_link_libraries(${CXX_EXE_NAME} GTest::gtest_main)
target_link_libraries(${CXX_EXE_NAME} ReflectionTemplateLib)
target_link_libraries(${CXX_EXE_NAME} CxxRTLTypeRegistration)

# Add the source directory
include(src/CMakeLists.txt)

include(GoogleTest)
gtest_discover_tests(${CXX_EXE_NAME})
