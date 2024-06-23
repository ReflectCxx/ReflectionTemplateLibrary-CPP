#include "Reflection.h"
#include "CxxMirrorBuilder.h"

//User defined types to be reflected.
#include "Complex.h"
#include "Date.h"

using namespace rtl::access;
using namespace rtl::builder;
using namespace test_project;

CxxMirror& MyReflection::instance()
{
	static CxxMirror cxxMirror({

		//Global function, not contained in any namespace.
		Reflect().function("getComplexNumAsString").build(getComplexNumAsString),

		//Global functions, in "complex" namespace.
		Reflect().nameSpace("complex").function("setReal").build(complex::setReal),
		Reflect().nameSpace("complex").function("setImaginary").build(complex::setImaginary),
		Reflect().nameSpace("complex").function("getMagnitude").build(complex::getMagnitude),

		//"Date" struct, in test_project namespace. Ctor, Date()
		Reflect().nameSpace("test_project").record("Date").constructor<Date>().build(),
		//Ctor, Date(std::string)
		Reflect().nameSpace("test_project").record("Date").constructor<Date>().build<std::string>(),
		//Ctor, Date(unsigned, unsigned, unsigned)
		Reflect().nameSpace("test_project").record("Date").constructor<Date>().build<unsigned, unsigned, unsigned>()

	});

	return cxxMirror;
}