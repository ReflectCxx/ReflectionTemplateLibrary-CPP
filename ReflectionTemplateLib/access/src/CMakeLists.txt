# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/CxxMirror.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Function.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Method.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Record.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/RStatus.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/UniqueAny.cpp"
)

SET(COMMON_HEADERS
	"${PROJECT_SOURCE_DIR}/common/Constants.h"
	"${PROJECT_SOURCE_DIR}/common/RTLibInterface.h"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/access/inc/CxxMirror.h"
	"${PROJECT_SOURCE_DIR}/access/inc/Function.h"
	"${PROJECT_SOURCE_DIR}/access/inc/Function.hpp"
	"${PROJECT_SOURCE_DIR}/access/inc/Method.h"
	"${PROJECT_SOURCE_DIR}/access/inc/Method.hpp"
	"${PROJECT_SOURCE_DIR}/access/inc/Record.h"
	"${PROJECT_SOURCE_DIR}/access/inc/Record.hpp"
	"${PROJECT_SOURCE_DIR}/access/inc/RStatus.h"
	"${PROJECT_SOURCE_DIR}/access/inc/UniqueAny.h"
)

# Add any additional source files if needed
target_sources(ReflectionTemplateLib
    PRIVATE
        "${LOCAL_HEADERS}"
		"${COMMON_HEADERS}"
		"${LOCAL_SOURCES}"
)


SOURCE_GROUP("Source Files\\Access" FILES ${LOCAL_SOURCES})
SOURCE_GROUP("Header Files\\Access" FILES ${LOCAL_HEADERS})