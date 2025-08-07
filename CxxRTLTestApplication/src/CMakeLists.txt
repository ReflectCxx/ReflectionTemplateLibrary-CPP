# CMakeLists.txt for CxxReflectionTests
cmake_minimum_required(VERSION 3.20)

project(CxxRTLTestApplication)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES_0
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ClassMethodsTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ConstMethodOverloadTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ConstructorTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/CopyConstructorTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/NameSpaceGlobalsTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ReflectedCallStatusErrTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/StaticMethodTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/PerfectForwardingTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/MoveConstructorTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ReturnValueReflectionTest.cpp"
)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES_1
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_bool.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_char.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_strings.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_int.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_arrays.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_stdUniquePtr.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_stdSharedPtr.cpp"
)

# Add any additional source files if needed
target_sources(CxxRTLTestApplication
    PRIVATE
		"${LOCAL_SOURCES_0}"
		"${LOCAL_SOURCES_1}"
)

SOURCE_GROUP("Source Files\\FunctionalityTests" FILES ${LOCAL_SOURCES_0})
SOURCE_GROUP("Source Files\\RObjectTests" FILES ${LOCAL_SOURCES_1})