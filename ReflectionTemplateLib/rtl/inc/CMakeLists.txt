# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/rtl/inc/CMakeLists.txt

# Collect local headers (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/CxxMirror.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/CxxMirrorToJson.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Function.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Function.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Method.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Method.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Record.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Record.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/RObject.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RObject.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/type_meta.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/type_meta.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/view.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/view.hpp"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\RTL" FILES ${LOCAL_HEADERS})
