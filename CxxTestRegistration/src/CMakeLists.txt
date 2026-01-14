# CMakeLists.txt for ReflectionTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(CxxTestRegistration)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/AnimalRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/BookRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/CalenderRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ComplexRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/DateRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/EventRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/LibraryRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/PersonRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/PodStdRegistration.cpp"
	
	"${CMAKE_CURRENT_LIST_DIR}/StrWrapRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StrMuteRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StrConstRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StrFuncsRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StrStaticRegistration.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StrConstOverloadRegistration.cpp"
	
	"${CMAKE_CURRENT_LIST_DIR}/TestMirrorProvider.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Registration.h"
	"${PROJECT_SOURCE_DIR}/inc/TestMirrorProvider.h"
)

# Add any additional source files if needed
target_sources(CxxTestRegistration
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)