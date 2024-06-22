#include "Reflection.h"
#include "CxxMirrorBuilder.h"

//User defined types to be reflected.
#include "Complex.h"
#include "Date.h"

using namespace rtl::access;
using namespace rtl::builder;
using namespace test_project;

namespace rtl_tests {

	CxxMirror& MyReflection::instance()
	{
		static CxxMirror cxxMirror({

			Reflect().function("getComplexNumAsString").build(getComplexNumAsString),

			Reflect().nameSpace("complex").function("setReal").build(complex::setReal),
			Reflect().nameSpace("complex").function("setImaginary").build(complex::setImaginary),
			Reflect().nameSpace("complex").function("getMagnitude").build(complex::getMagnitude),

			//Constructor registration, Date()
			Reflect().nameSpace("test_project").record("Date").constructor<Date>().build(),

			//Constructor registration, Date(std::string)
			Reflect().nameSpace("test_project").record("Date").constructor<Date>().build<std::string>(),

			Reflect().nameSpace("test_project").record("Date").function("getDateAsString").build(&Date::getDateAsString)
		});

		return cxxMirror;
	}
}