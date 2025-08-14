# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/CxxMirror.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/CxxMirrorToJson.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Function.cpp"
)

SET(COMMON_HEADERS
	
	"${PROJECT_SOURCE_DIR}/common/view.h"
	"${PROJECT_SOURCE_DIR}/common/view.hpp"
	"${PROJECT_SOURCE_DIR}/common/Constants.h"
	"${PROJECT_SOURCE_DIR}/common/rtl_traits.h"
	"${PROJECT_SOURCE_DIR}/common/ConversionUtils.h"
	"${PROJECT_SOURCE_DIR}/common/RTLibInterface.h"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/access/inc/CxxMirror.h"
	"${PROJECT_SOURCE_DIR}/access/inc/CxxMirror.hpp"
	"${PROJECT_SOURCE_DIR}/access/inc/CxxMirrorToJson.h"
	"${PROJECT_SOURCE_DIR}/access/inc/Function.h"
	"${PROJECT_SOURCE_DIR}/access/inc/Function.hpp"
	"${PROJECT_SOURCE_DIR}/access/inc/FunctionCaller.h"
	"${PROJECT_SOURCE_DIR}/access/inc/FunctionCaller.hpp"
	"${PROJECT_SOURCE_DIR}/access/inc/Method.h"
	"${PROJECT_SOURCE_DIR}/access/inc/Method.hpp"
	"${PROJECT_SOURCE_DIR}/access/inc/MethodInvoker.h"
	"${PROJECT_SOURCE_DIR}/access/inc/MethodInvoker.hpp"
	"${PROJECT_SOURCE_DIR}/access/inc/Record.h"
	"${PROJECT_SOURCE_DIR}/access/inc/RObject.h"
	"${PROJECT_SOURCE_DIR}/access/inc/RObject.hpp"
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