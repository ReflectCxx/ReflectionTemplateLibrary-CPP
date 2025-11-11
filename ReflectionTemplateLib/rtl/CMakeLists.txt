# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/rtl/CMakeLists.txt

# Top-level headers in rtl/ (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/access.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/builder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_forward_decls.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_constants.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_errors.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_traits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_typeid.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\RTL" FILES ${LOCAL_HEADERS})

# Add subdirectories
add_subdirectory(inc)
add_subdirectory(src)
add_subdirectory(builder)
add_subdirectory(cache)
add_subdirectory(detail)
add_subdirectory(erasure)
add_subdirectory(dispatch)