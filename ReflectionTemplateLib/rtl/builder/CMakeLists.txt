# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/builder/CMakeLists.txt

# Collect all headers in builder/ (absolute paths)
set(LOCAL_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/Builder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Builder.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ConstructorBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/FunctorContainer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/MethodContainer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RecordBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RecordBuilder.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Reflect.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Reflect.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ReflectionBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ReflectionBuilder.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/RegisterCtor.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/RegisterFunction.h"  
    "${CMAKE_CURRENT_SOURCE_DIR}/RObjectBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/RObjectBuilder.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SetupDispatch.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/SetupMethod.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/SetupMethod.hpp"
	
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Builder" FILES ${LOCAL_HEADERS})