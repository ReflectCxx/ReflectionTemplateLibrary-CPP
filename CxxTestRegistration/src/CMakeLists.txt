# CMakeLists.txt for ReflectionTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(CxxTestRegistration)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/TestMirrorProvider.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/TestMirrorProvider.h"
)

# Add any additional source files if needed
target_sources(CxxTestRegistration
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)