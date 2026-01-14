# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/rtl/CMakeLists.txt

# Top-level headers in rtl/ (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_errors.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_traits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_typeid.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_constants.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_forward_decls.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_constructor.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_function.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_function_erased_return.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_const.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased_return.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased_target.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\RTL" FILES ${LOCAL_HEADERS})

add_subdirectory(inc)
add_subdirectory(src)
add_subdirectory(builder)
add_subdirectory(detail)
add_subdirectory(dispatch)
