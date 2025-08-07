# CMakeLists.txt for ReflectionTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(CxxRTLTypeRegistration)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/MyReflection.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/MyReflection.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProps/inc/Book.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProps/inc/Complex.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProps/inc/Date.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProps/inc/Person.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProps/inc/Animal.h"
)

# Add any additional source files if needed
target_sources(CxxRTLTypeRegistration
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)