# Create a variable containing the source files for your target
set(LOCAL_SOURCES
	"${CMAKE_CURRENT_LIST_DIR}/Book.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Date.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Person.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Animal.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Library.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Complex.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StringOps.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StringWrap.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StringMute.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StringConst.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StringStatic.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/StringConstOverload.cpp"
)

SET(LOCAL_HEADERS
	"${PROJECT_SOURCE_DIR}/inc/Book.h"
	"${PROJECT_SOURCE_DIR}/inc/Date.h"
	"${PROJECT_SOURCE_DIR}/inc/Animal.h"
	"${PROJECT_SOURCE_DIR}/inc/Person.h"
	"${PROJECT_SOURCE_DIR}/inc/Library.h"
	"${PROJECT_SOURCE_DIR}/inc/Complex.h"
	"${PROJECT_SOURCE_DIR}/inc/StringOps.h"
	"${PROJECT_SOURCE_DIR}/inc/StringWrap.h"
	"${PROJECT_SOURCE_DIR}/inc/StringMute.h"
	"${PROJECT_SOURCE_DIR}/inc/StringConst.h"
	"${PROJECT_SOURCE_DIR}/inc/StringStatic.h"
	"${PROJECT_SOURCE_DIR}/inc/StringConstOverload.h"	
)

# Add any additional source files if needed
target_sources(CxxTestProps
    PRIVATE
        "${LOCAL_HEADERS}"
		"${LOCAL_SOURCES}"
)