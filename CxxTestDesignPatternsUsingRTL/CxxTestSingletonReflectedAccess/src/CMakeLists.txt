# CMakeLists.txt for CxxTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(CxxTestSingletonReflectedAccess)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/main.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Singleton.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/SingletonReflection.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Singleton.h"
	"${PROJECT_SOURCE_DIR}/inc/SingletonReflection.h"
)

# Add any additional source files if needed
target_sources(CxxTestSingletonReflectedAccess
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)