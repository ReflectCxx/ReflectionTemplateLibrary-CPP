# CMakeLists.txt for CxxTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(CxxTestProxyDesignPattern)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/main.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Original.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/OriginalReflection.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Proxy.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Original.h"
	"${PROJECT_SOURCE_DIR}/inc/OriginalReflection.h"
	"${PROJECT_SOURCE_DIR}/inc/Proxy.h"
	"${PROJECT_SOURCE_DIR}/inc/Proxy.hpp"
)

# Add any additional source files if needed
target_sources(CxxTestProxyDesignPattern
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)