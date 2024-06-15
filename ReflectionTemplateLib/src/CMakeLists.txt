# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/CxxMirrorBuilder.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Function.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/NameSpace.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Record.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Constants.h"
	"${PROJECT_SOURCE_DIR}/inc/CxxMirror.h"
    "${PROJECT_SOURCE_DIR}/inc/CxxMirror.hpp"
	"${PROJECT_SOURCE_DIR}/inc/CxxMirrorBuilder.h"
    "${PROJECT_SOURCE_DIR}/inc/FunctorContainer.h"
    "${PROJECT_SOURCE_DIR}/inc/FunctorContainer.hpp"
	"${PROJECT_SOURCE_DIR}/inc/Function.h"
	"${PROJECT_SOURCE_DIR}/inc/Function.hpp"
	"${PROJECT_SOURCE_DIR}/inc/NameSpace.h"
	"${PROJECT_SOURCE_DIR}/inc/Record.h"
    "${PROJECT_SOURCE_DIR}/inc/SignatureTypeList.h"
    "${PROJECT_SOURCE_DIR}/inc/TypeList.h"
)

# Add any additional source files if needed
target_sources(ReflectionTemplateLib
    PRIVATE
        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)