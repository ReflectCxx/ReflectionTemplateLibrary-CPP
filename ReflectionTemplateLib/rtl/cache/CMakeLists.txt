# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/cache/CMakeLists.txt

# Collect headers (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/cache_lambda_method.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/cache_lambda_function.h"
    
	"${CMAKE_CURRENT_SOURCE_DIR}/cache_method_ptr.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/cache_function_ptr.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/cache_method_ptr_const.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Cache" FILES ${LOCAL_HEADERS})