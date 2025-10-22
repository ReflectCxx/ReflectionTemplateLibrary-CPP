# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/erasure/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS

	"${CMAKE_CURRENT_SOURCE_DIR}/erasure_base.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erasure_base.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/erase_return.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erase_return_n_target.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erase_return_aware_target.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erase_target_aware_return.h"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/aware_return.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/aware_return_n_target.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/aware_return_n_target_const.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Erasure" FILES ${LOCAL_HEADERS})
