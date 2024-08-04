# CMakeLists.txt for CxxTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(CxxTypeRegistration)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/MyReflection.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestUtilsBook.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestUtilsDate.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestUtilsPerson.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Book.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Complex.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Date.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Person.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/MyReflection.h"
	"${PROJECT_SOURCE_DIR}/inc/TestUtilsBook.h"
	"${PROJECT_SOURCE_DIR}/inc/TestUtilsDate.h"
	"${PROJECT_SOURCE_DIR}/inc/TestUtilsGlobals.h"
	"${PROJECT_SOURCE_DIR}/inc/TestUtilsPerson.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Book.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Complex.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Date.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Person.h"
)

# Add any additional source files if needed
target_sources(CxxTypeRegistration
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)