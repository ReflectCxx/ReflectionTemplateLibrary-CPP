# CMakeLists.txt for CxxTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(ReflectionTemplateLibUnitTests)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/RObjectUnitTests_strings.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/RObjectUnitTests_strings.h"
)

# Add any additional source files if needed
target_sources(ReflectionTemplateLibUnitTests
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)