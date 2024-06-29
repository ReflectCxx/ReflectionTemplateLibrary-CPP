# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/ReflectTypeMeta.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/TypeId.cpp"
)


SET(LOCAL_HEADERS
    "${PROJECT_SOURCE_DIR}/detail/inc/FunctorContainer.h"
    "${PROJECT_SOURCE_DIR}/detail/inc/FunctorContainer.hpp"
	"${PROJECT_SOURCE_DIR}/detail/inc/ReflectTypeMeta.h"
	"${PROJECT_SOURCE_DIR}/detail/inc/TypeId.h"
)

# Add any additional source files if needed
target_sources(ReflectionTemplateLib
    PRIVATE
        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)


SOURCE_GROUP("Source Files\\Detail" FILES ${LOCAL_SOURCES})
SOURCE_GROUP("Header Files\\Detail" FILES ${LOCAL_HEADERS})