# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/Book.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Date.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Person.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Animal.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Library.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ComplexStrings.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Book.h"
	"${PROJECT_SOURCE_DIR}/inc/Date.h"
	"${PROJECT_SOURCE_DIR}/inc/Animal.h"
	"${PROJECT_SOURCE_DIR}/inc/Person.h"
	"${PROJECT_SOURCE_DIR}/inc/Library.h"
	"${PROJECT_SOURCE_DIR}/inc/ComplexStrings.h"
)

# Add any additional source files if needed
target_sources(CxxTestProps
    PRIVATE
        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)