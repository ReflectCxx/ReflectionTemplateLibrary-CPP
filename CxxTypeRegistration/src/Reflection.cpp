#include "Reflection.h"
#include "CxxMirrorBuilder.h"
#include "NSFunction.h"

using namespace rtl;

namespace rtl_tests {

	const bool CxxReflection::init = CxxReflection::Reflection::init();

	CxxReflection::Reflection& CxxReflection::instance()
	{
		static Reflection cxxReflector({

			Reflect().nameSpace("book").function("addBookInfo").build(book::addBookInfo),
			Reflect().nameSpace("book").function("showBookInfo").build(book::showBookInfo),
			Reflect().nameSpace("person").function("setProfile").build(person::setProfile),
			Reflect().nameSpace("person").function("showProfile").build(person::showProfile)

		});

		return cxxReflector;
	}
}