# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/detail/inc/CMakeLists.txt

# All headers in this folder (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/ConversionUtils.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/CxxReflection.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ReflectCast.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ReflectCast.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ReflectCastUtil.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RObjectId.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RObjectUPtr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RObjExtracter.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/RObjectBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RObjectBuilder.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/HopBuilderFunction.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/HopBuilderFunction.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/HopBuilderMethod.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/HopBuilderMethod.hpp"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Detail" FILES ${LOCAL_HEADERS})