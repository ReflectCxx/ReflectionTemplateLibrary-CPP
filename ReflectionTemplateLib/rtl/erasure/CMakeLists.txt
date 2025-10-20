# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/erasure/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS

	"${CMAKE_CURRENT_SOURCE_DIR}/erase_fn_base.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erase_return_fn.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/erase_return_fn_rec.h"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/aware_return_fn.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/aware_return_fn_rec.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/aware_return_fn_rec_const.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Erasure" FILES ${LOCAL_HEADERS})
