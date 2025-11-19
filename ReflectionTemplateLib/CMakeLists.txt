cmake_minimum_required(VERSION 3.20)

project(ReflectionTemplateLib LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library target (static or shared)
add_library(${PROJECT_NAME} STATIC)

# Public include paths for this library
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/rtl/builder
        ${CMAKE_CURRENT_SOURCE_DIR}/rtl/detail
        ${CMAKE_CURRENT_SOURCE_DIR}/rtl/dispatch
        ${CMAKE_CURRENT_SOURCE_DIR}/rtl/inc
		${CMAKE_CURRENT_SOURCE_DIR}/rtl
)

# Add subdirectories
add_subdirectory(rtl)