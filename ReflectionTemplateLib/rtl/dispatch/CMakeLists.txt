# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/dispatch/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/functor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/functor_cast.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/forward_call.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/cache_method_ptr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/cache_function_ptr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/cache_method_ptr_const.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/method_ptr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/method_ptr.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/method_lambda.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/method_ptr_const.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/method_ptr_const.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/function_ptr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/function_ptr.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/function_lambda.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/aware_return.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/aware_constructor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/aware_return_n_target.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/aware_return_n_target_const.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Dispatch" FILES ${LOCAL_HEADERS})