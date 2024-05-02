# Create a variable containing the source files for your target
set(LOCAL_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/CppMirror.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ReflClass.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/ReflMethod.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ReflVariable.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/ClassReflection.h"
    "${PROJECT_SOURCE_DIR}/inc/ClassReflection.hpp"
    "${PROJECT_SOURCE_DIR}/inc/ConstructorReflection.h"
	"${PROJECT_SOURCE_DIR}/inc/ConstructorReflection.hpp"
	"${PROJECT_SOURCE_DIR}/inc/CppTypeReflection.h"
    "${PROJECT_SOURCE_DIR}/inc/MethodReflection.h"
    "${PROJECT_SOURCE_DIR}/inc/MethodReflection.hpp"	
	"${PROJECT_SOURCE_DIR}/inc/ReflClassBuilder.h"
    "${PROJECT_SOURCE_DIR}/inc/ReflClassBuilder.hpp"
    "${PROJECT_SOURCE_DIR}/inc/ReflectionBuilder.h"
	"${PROJECT_SOURCE_DIR}/inc/ReflectionBuilder.hpp"
	"${PROJECT_SOURCE_DIR}/inc/ReflectionTemplateBuilder.h"	
	"${PROJECT_SOURCE_DIR}/inc/ReflExecuter.h"
    "${PROJECT_SOURCE_DIR}/inc/ReflExecuter.hpp"
    "${PROJECT_SOURCE_DIR}/inc/ReflInheritanceBuilder.h"
	"${PROJECT_SOURCE_DIR}/inc/ReflInheritanceBuilder.hpp"
    "${PROJECT_SOURCE_DIR}/inc/ReflObject.h"
	"${PROJECT_SOURCE_DIR}/inc/ReflObject.hpp"
    "${PROJECT_SOURCE_DIR}/inc/TypeConstants.h"
    "${PROJECT_SOURCE_DIR}/inc/VarReflection.h"
	"${PROJECT_SOURCE_DIR}/inc/VarReflection.h"
)

# Add any additional source files if needed
target_sources(CxxReflectionTemplates
    PUBLIC
		"${PROJECT_SOURCE_DIR}/inc/CppMirror.h"
		"${PROJECT_SOURCE_DIR}/inc/ReflClass.h"
		"${PROJECT_SOURCE_DIR}/inc/ReflClass.hpp"
		"${PROJECT_SOURCE_DIR}/inc/ReflMethod.h"
		"${PROJECT_SOURCE_DIR}/inc/ReflMethod.hpp"
		"${PROJECT_SOURCE_DIR}/inc/ReflVariable.h"	
		"${PROJECT_SOURCE_DIR}/inc/ReflVariable.hpp"
    PRIVATE
        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)