# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/CxxReflection.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ReflectCast.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RObjectConverters_string.cpp"
)


SET(LOCAL_HEADERS

	"${PROJECT_SOURCE_DIR}/detail/inc/LambdaBridge.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/LambdaRegistry.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/FunctorRegistry.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/CallReflector.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/CxxReflection.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/FunctionCaller.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/FunctionCaller.hpp"
	"${PROJECT_SOURCE_DIR}/detail/inc/MethodInvoker.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/MethodInvoker.hpp"
    "${PROJECT_SOURCE_DIR}/detail/inc/FunctorContainer.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/FunctorId.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/RObjectId.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/MethodContainer.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/ReflectCast.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/ReflectCast.hpp"
	"${PROJECT_SOURCE_DIR}/detail/inc/ReflectCastUtil.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/ReflectionBuilder.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/ReflectionBuilder.hpp"
	"${PROJECT_SOURCE_DIR}/detail/inc/SetupConstructor.h"
    "${PROJECT_SOURCE_DIR}/detail/inc/SetupConstructor.hpp"
	"${PROJECT_SOURCE_DIR}/detail/inc/SetupFunction.h"
    "${PROJECT_SOURCE_DIR}/detail/inc/SetupFunction.hpp"
	"${PROJECT_SOURCE_DIR}/detail/inc/SetupMethod.h"
    "${PROJECT_SOURCE_DIR}/detail/inc/SetupMethod.hpp"
	"${PROJECT_SOURCE_DIR}/detail/inc/TypeId.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/RObjectUPtr.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/RObjExtracter.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/RObjectBuilder.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/RObjectBuilder.hpp"
)


# Add any additional source files if needed
target_sources(ReflectionTemplateLib
    PRIVATE
        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)


SOURCE_GROUP("Source Files\\Detail" FILES ${LOCAL_SOURCES})
SOURCE_GROUP("Header Files\\Detail" FILES ${LOCAL_HEADERS})