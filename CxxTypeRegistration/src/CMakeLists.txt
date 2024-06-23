# CMakeLists.txt for CxxTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(CxxTypeRegistration)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/Reflection.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestUtils.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Book.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Date.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Complex.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Reflection.h"
	"${PROJECT_SOURCE_DIR}/inc/TestUtils.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Book.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Date.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Complex.h"
)

# Add any additional source files if needed
target_sources(CxxTypeRegistration
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)