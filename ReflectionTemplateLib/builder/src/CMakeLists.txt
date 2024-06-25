# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/Reflect.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/FunctionBuilder.cpp"
)

SET(COMMON_HEADERS
	"${PROJECT_SOURCE_DIR}/common/Constants.h"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/builder/inc/ConstructorBuilder.h"
	"${PROJECT_SOURCE_DIR}/builder/inc/ConstructorBuilder.hpp"
	"${PROJECT_SOURCE_DIR}/builder/inc/FunctionBuilder.h"
	"${PROJECT_SOURCE_DIR}/builder/inc/FunctionBuilder.hpp"
	"${PROJECT_SOURCE_DIR}/builder/inc/RecordBuilder.h"
	"${PROJECT_SOURCE_DIR}/builder/inc/RecordBuilder.hpp"
	"${PROJECT_SOURCE_DIR}/builder/inc/Reflect.h"
	"${PROJECT_SOURCE_DIR}/builder/inc/Reflect.hpp"
)

# Add any additional source files if needed
target_sources(ReflectionTemplateLib
    PRIVATE
        "${LOCAL_HEADERS}"
		"${COMMON_HEADERS}"
		"${LOCAL_SOURCES}"
)

SOURCE_GROUP("Source Files\\Builder" FILES ${LOCAL_SOURCES})
SOURCE_GROUP("Header Files\\Builder" FILES ${LOCAL_HEADERS})