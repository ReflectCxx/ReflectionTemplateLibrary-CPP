# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/cache/CMakeLists.txt

# Collect headers (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/lambda_method_cache.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/lambda_function_cache.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/functor_cache.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/functor_cache_const.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/functor_cache_nonconst.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Cache" FILES ${LOCAL_HEADERS})