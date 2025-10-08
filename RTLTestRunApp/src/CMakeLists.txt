# CMakeLists.txt for CxxReflectionTests
cmake_minimum_required(VERSION 3.20)

project(RTLTestRunApp)

# Create a variable containing the source files for your target
set(LOCAL_SOURCES_0
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ClassMethodsTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/StaticTypeCFunctionTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ConstMethodOverloadTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ConstructorTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/CopyConstructorTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/NameSpaceGlobalsTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ReflectionOpErrorCodeTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/StaticMethodTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/PerfectForwardingTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/MoveConstructorTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/ReturnValueReflectionTest.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/TypeErasedReflectiveCalls/BasicTypeErasedDispatch.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionalityTests/StaticTypeReflectiveCalls/StrictStaticTypeDispatch.cpp"
)

# Create a variable containing the source files for your target
set(LOCAL_ROBJECT
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_bool.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_char.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_strings.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_int.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_arrays.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_stdUniquePtr.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectReflecting_stdSharedPtr.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectTests/RObjectImplicitConversions.cpp"
)

set(LOCAL_MY_REFLECTION
	"${CMAKE_CURRENT_LIST_DIR}/MyReflectionTests/MyReflectingType.h"
	"${CMAKE_CURRENT_LIST_DIR}/MyReflectionTests/MyReflectionTests.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/MyReflectionTests/MyCxxTestRegistration.cpp"
)


set(LOCAL_CXXMIRROR
	"${CMAKE_CURRENT_LIST_DIR}/CxxMirrorTests/CxxMirrorObjectTest.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/CxxMirrorTests/CxxMirrorThreadingTest.h"
	"${CMAKE_CURRENT_LIST_DIR}/CxxMirrorTests/CxxMirrorThreadingTest.cpp"
)


# Add any additional source files if needed
target_sources(RTLTestRunApp
    PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/main.cpp"
		"${LOCAL_SOURCES_0}"
		"${LOCAL_ROBJECT}"
		"${LOCAL_CXXMIRROR}"
		"${LOCAL_MY_REFLECTION}"
)

SOURCE_GROUP("Source Files\\FunctionalityTests" FILES ${LOCAL_SOURCES_0})
SOURCE_GROUP("Source Files\\RObjectTests" FILES ${LOCAL_ROBJECT})
SOURCE_GROUP("Source Files\\CxxMirrorTests" FILES ${LOCAL_CXXMIRROR})
SOURCE_GROUP("Source Files\\MyReflectionTests" FILES ${LOCAL_MY_REFLECTION})