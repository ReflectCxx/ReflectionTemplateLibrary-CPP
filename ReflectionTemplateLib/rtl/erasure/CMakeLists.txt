# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/erasure/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/erase_function.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erase_method.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/return_function.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/return_method.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/return_const_method.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Erasure" FILES ${LOCAL_HEADERS})
