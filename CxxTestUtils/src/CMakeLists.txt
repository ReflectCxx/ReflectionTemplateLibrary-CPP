# CMakeLists.txt for CxxTestUtils
cmake_minimum_required(VERSION 3.20)

project(CxxTestUtils)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/TestUtilsBook.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestUtilsDate.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestUtilsPerson.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestUtilsAnimal.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/GlobalTestUtils.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Book.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Complex.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Date.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Person.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Animal.cpp"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/src/Library.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/TestUtilsBook.h"
	"${PROJECT_SOURCE_DIR}/inc/TestUtilsDate.h"
	"${PROJECT_SOURCE_DIR}/inc/GlobalTestUtils.h"
	"${PROJECT_SOURCE_DIR}/inc/TestUtilsPerson.h"
	"${PROJECT_SOURCE_DIR}/inc/TestUtilsAnimal.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Book.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Complex.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Date.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Person.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Animal.h"
	"${CMAKE_SOURCE_DIR}/CxxTestProject/inc/Library.h"
)

# Add any additional source files if needed
target_sources(CxxTestUtils
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)