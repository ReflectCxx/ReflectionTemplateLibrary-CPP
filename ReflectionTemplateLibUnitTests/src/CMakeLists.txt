# CMakeLists.txt for CxxTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(ReflectionTemplateLibUnitTests)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/RObjectConversions_bool.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectConversions_char.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectConversions_strings.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectConversions_int.cpp"
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