# CMakeLists.txt for CxxReflectionTests
cmake_minimum_required(VERSION 3.20)

project(CxxReflectionTests)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/ClassMethodsTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ConstructorTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/NameSpaceGlobalsTests.cpp"
)

# Add any additional source files if needed
target_sources(CxxReflectionTests
    PUBLIC
		"${LOCAL_SOURCES}"
)