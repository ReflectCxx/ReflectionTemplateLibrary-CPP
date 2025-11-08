
#include <Reflect.hpp>

#include "Complex.h"
#include "Registration.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace test_mirror
{
	void registerTypeComplex(std::vector<rtl::Function>& fns)
	{
		//  Unique function, no overloads, no need to specify signature as template parameters.
		fns.push_back(rtl::type().function(str_getComplexNumAsString)
								 .build(getComplexNumAsString));

	/* Grouping functions under a namespace, which is optional. they can be registered without it as well.
		but if registered under namspace, then to retrieve it from CxxMirror object, namespace name must be passed,
		e.g. cxx::mirror().getFunction("namespace_name", "function_name") & cxx::mirror().getRecord("namespace_name", "record_name") */  
		fns.push_back(rtl::type().ns(str_complex)
								 .function(str_setReal)
								 .build(complex::setReal));
		
		fns.push_back(rtl::type().ns(str_complex)
								 .function(str_setImaginary)
								 .build(complex::setImaginary));
		
		fns.push_back(rtl::type().ns(str_complex)
								 .function(str_getMagnitude)
								 .build(complex::getMagnitude));
	}
}