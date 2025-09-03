# CMakeLists.txt for ReflectionTemplateLib

cmake_minimum_required(VERSION 3.20)

# Project definition
project(ReflectionTemplateLib LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library target
add_library(${PROJECT_NAME} STATIC)

# Public include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/common
        ${CMAKE_CURRENT_SOURCE_DIR}/detail/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/access/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/builder/inc
)

# Add subdirectories for sources
add_subdirectory(detail/src)
add_subdirectory(access/src)
add_subdirectory(builder)