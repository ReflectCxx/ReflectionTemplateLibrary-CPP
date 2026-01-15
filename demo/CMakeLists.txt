cmake_minimum_required(VERSION 3.20)
project(RTLDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_EXE_NAME RTLDemoApp)

add_executable(${CXX_EXE_NAME}
    main.cpp
    Person/Person.h
    MyReflection/MyReflection.cpp
    MyReflection/MyReflection.h
)

target_link_libraries(${CXX_EXE_NAME}
    PRIVATE
        ReflectionTemplateLib
)