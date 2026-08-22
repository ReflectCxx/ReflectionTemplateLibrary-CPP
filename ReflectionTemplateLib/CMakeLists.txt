cmake_minimum_required(VERSION 3.20)

project(ReflectionTemplateLib LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_access.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_builder.h"
)

target_sources(${PROJECT_NAME} PRIVATE ${LOCAL_HEADERS})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/rtl
)

add_subdirectory(rtl)
