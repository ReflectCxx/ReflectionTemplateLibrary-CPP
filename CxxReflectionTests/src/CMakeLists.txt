# CMakeLists.txt for CxxReflectionTests
cmake_minimum_required(VERSION 3.20)

project(CxxReflectionTests)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/RTLUnitTests.cpp"
)

#SET(LOCAL_HEADERS
#	"${PROJECT_SOURCE_DIR}/inc/Book.h"
#	"${PROJECT_SOURCE_DIR}/inc/Reflection.h"
#)

# Add any additional source files if needed
target_sources(CxxReflectionTests
    PUBLIC
#        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)