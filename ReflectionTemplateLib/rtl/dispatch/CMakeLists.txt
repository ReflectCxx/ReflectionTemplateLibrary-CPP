# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/dispatch/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS
	
	"${CMAKE_CURRENT_SOURCE_DIR}/functor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/function_ptr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/method_ptr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/const_method_ptr.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/lambda.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/lambda_method.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/lambda_function.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Dispatch" FILES ${LOCAL_HEADERS})
