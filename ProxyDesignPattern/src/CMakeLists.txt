# CMakeLists.txt for CxxTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(ProxyDesignPattern)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/main.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Original.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/OrgReflection.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Proxy.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Original.h"
	"${PROJECT_SOURCE_DIR}/inc/OrgReflection.h"
	"${PROJECT_SOURCE_DIR}/inc/Proxy.h"
)

# Add any additional source files if needed
target_sources(ProxyDesignPattern
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)