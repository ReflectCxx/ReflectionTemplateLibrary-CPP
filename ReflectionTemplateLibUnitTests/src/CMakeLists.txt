# CMakeLists.txt for RObject Reflection tests.
cmake_minimum_required(VERSION 3.20)

project(ReflectionTemplateLibUnitTests)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/RObjectReflecting_bool.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectReflecting_char.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectReflecting_strings.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectReflecting_int.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectReflecting_arrays.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/ReflectionSystem.h"
)

# Add any additional source files if needed
target_sources(ReflectionTemplateLibUnitTests
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)