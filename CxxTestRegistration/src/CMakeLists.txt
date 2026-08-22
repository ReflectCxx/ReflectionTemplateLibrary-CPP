# CMakeLists.txt for ReflectionTypeRegistration
cmake_minimum_required(VERSION 3.20)

project(CxxTestRegistration)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES	
	"${CMAKE_CURRENT_LIST_DIR}/regs0_Animal.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs1_Date.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs2_Book.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs3_Person.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs4_StringMute.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs5_StringStatic.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs6_StringConstOverload.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs7_StringOps.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs8_StringWrap.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs9_Library.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs10_Complex.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/regs11_StringConst.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TestMirrorProvider.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/reg_ids.h"
	"${PROJECT_SOURCE_DIR}/inc/reg_decls.h"
	"${PROJECT_SOURCE_DIR}/inc/TestMirrorProvider.h"
)

# Add any additional source files if needed
target_sources(CxxTestRegistration
	PRIVATE
		"${LOCAL_SOURCES}"
        "${LOCAL_HEADERS}"
)