# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/dispatch/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS
	
	"${CMAKE_CURRENT_SOURCE_DIR}/dispatch_interface.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/functor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/functor_const.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/functor_nonconst.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/lambda.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/lambda_ctor.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/lambda_function.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lambda_copy_ctor.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lambda_method_const.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lambda_method_nonconst.hpp"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/CallReflector.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/FunctionCaller.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/FunctionCaller.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MethodInvoker.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/MethodInvoker.hpp"

)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Dispatch" FILES ${LOCAL_HEADERS})