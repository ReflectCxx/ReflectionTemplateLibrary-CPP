# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/Book.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Date.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Complex.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Book.h"
	"${PROJECT_SOURCE_DIR}/inc/Date.h"
	"${PROJECT_SOURCE_DIR}/inc/Complex.h"
)

# Add any additional source files if needed
target_sources(CxxTestProject
    PRIVATE
        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)