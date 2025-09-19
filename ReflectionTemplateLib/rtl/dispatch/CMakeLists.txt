# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/dispatch/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS
	
	"${CMAKE_CURRENT_SOURCE_DIR}/dispatch_interface.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/functor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/functor_const.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/functor_nonconst.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/lambda.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/hopper.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/hopper_ctor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/hopper_const.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/hopper_nonconst.h"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/CallReflector.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/FunctionCaller.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/FunctionCaller.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MethodInvoker.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/MethodInvoker.hpp"

)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Dispatch" FILES ${LOCAL_HEADERS})
