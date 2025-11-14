# ReflectionTemplateLibrary-CPP/ReflectionTemplateLib/dispatch/CMakeLists.txt

# Collect headers in this folder (absolute paths)
set(LOCAL_HEADERS
	
	"${CMAKE_CURRENT_SOURCE_DIR}/functor.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/fn_meta.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/fn_signature.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/fn_signature_rec.h"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/method_ptr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/function_ptr.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/method_ptr_const.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/lambda_base.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/lambda_method.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/lambda_function.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_function.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/rtl_function_erased_return.h"
	
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased_return.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased_target.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_const.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased_const.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased_return_const.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/rtl_method_erased_target_const.h"
)

target_sources(ReflectionTemplateLib PRIVATE ${LOCAL_HEADERS})
source_group("Header Files\\Dispatch" FILES ${LOCAL_HEADERS})
