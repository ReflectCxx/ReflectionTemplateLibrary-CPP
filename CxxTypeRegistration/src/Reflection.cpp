#include "Reflection.h"
#include "CxxMirrorBuilder.h"

//User defined types to be reflected.
#include "NSFunction.h"
#include "Date.h"

using namespace rtl::access;
using namespace rtl::builder;
using namespace test_project;

namespace rtl_tests {

	CxxMirror& MyReflection::instance()
	{
		static CxxMirror cxxMirror({

			Reflect().nameSpace("book").function("addBookInfo").build(book::addBookInfo),
			Reflect().nameSpace("book").function("showBookInfo").build(book::showBookInfo),
			Reflect().nameSpace("person").function("setProfile").build(person::setProfile),
			Reflect().nameSpace("person").function("showProfile").build(person::showProfile),

			//Constructor registration, Date()
			Reflect().nameSpace("test_project").record("Date").constructor<Date>().build(),

			//Constructor registration, Date(std::string)
			Reflect().nameSpace("test_project").record("Date").constructor<Date>().build<std::string>(),

			Reflect().nameSpace("test_project").record("Date").function("getDateAsString").build(&Date::getDateAsString)
		});

		return cxxMirror;
	}
}