# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/erasure/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS

	"${CMAKE_CURRENT_SOURCE_DIR}/erasure_base.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erased_hopper.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erased_method_hop.h"
	
    "${CMAKE_CURRENT_SOURCE_DIR}/aware_method.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/aware_function.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/aware_method_const.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Erasure" FILES ${LOCAL_HEADERS})
