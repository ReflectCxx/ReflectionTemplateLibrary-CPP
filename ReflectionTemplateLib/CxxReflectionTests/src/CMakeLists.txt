# CMakeLists.txt for CxxReflectionTests
cmake_minimum_required(VERSION 3.20)

project(CxxReflectionTests)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Book.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ConstructorTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InheritanceTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/MethodCallTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Reflection.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestFact.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RTLUnitTests.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Book.h"
    "${PROJECT_SOURCE_DIR}/inc/ConstructorTests.h"
    "${PROJECT_SOURCE_DIR}/inc/InheritanceTests.h"
	"${PROJECT_SOURCE_DIR}/inc/MethodCallTests.h"
	"${PROJECT_SOURCE_DIR}/inc/Reflection.h"
    "${PROJECT_SOURCE_DIR}/inc/TestConstants.h"
    "${PROJECT_SOURCE_DIR}/inc/TestFact.hpp"	
	"${PROJECT_SOURCE_DIR}/inc/TestFact.h"
)

# Add any additional source files if needed
target_sources(CxxReflectionTests
    PUBLIC
        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)