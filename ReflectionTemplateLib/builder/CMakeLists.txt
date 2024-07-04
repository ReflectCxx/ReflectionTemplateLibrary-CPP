# Create a variable containing the source files for your target

SET(COMMON_HEADERS
	"${PROJECT_SOURCE_DIR}/common/Constants.h"
)

SET(LOCAL_HEADERS
	"${CMAKE_CURRENT_LIST_DIR}/inc/ConstructorBuilder.h"
	"${CMAKE_CURRENT_LIST_DIR}/inc/ConstructorBuilder.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/inc/Builder.h"
	"${CMAKE_CURRENT_LIST_DIR}/inc/Builder.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/inc/RecordBuilder.h"
	"${CMAKE_CURRENT_LIST_DIR}/inc/RecordBuilder.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/inc/Reflect.h"
	"${CMAKE_CURRENT_LIST_DIR}/inc/Reflect.hpp"
	"${CMAKE_CURRENT_LIST_DIR}/inc/ReflectionBuilder.h"
	"${CMAKE_CURRENT_LIST_DIR}/inc/ReflectionBuilder.hpp"
)

# Add any additional source files if needed
target_sources(ReflectionTemplateLib
    PRIVATE
        "${LOCAL_HEADERS}"
		"${COMMON_HEADERS}"
)

SOURCE_GROUP("Header Files\\Builder" FILES ${LOCAL_HEADERS})