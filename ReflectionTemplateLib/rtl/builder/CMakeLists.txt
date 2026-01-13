# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/builder/CMakeLists.txt

# Collect all headers in builder/ (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/Builder.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/ConstructorBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RecordBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Reflect.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ReflectionBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RegisterCtor.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/RegisterMethod.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/RegisterFunction.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/SetupDispatch.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Builder" FILES ${LOCAL_HEADERS})