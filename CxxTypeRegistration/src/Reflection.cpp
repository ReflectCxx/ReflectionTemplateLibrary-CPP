#include "Reflection.h"
#include "CxxMirrorBuilder.h"
#include "NSFunction.h"
#include "Date.h"

using namespace rtl;
using namespace test_project;

namespace rtl_tests {

	//This needs to be run before all. It initializes the ids to the types registered as template parameters.
	const bool CxxReflection::init = CxxReflection::Reflection::init();

	CxxReflection::Reflection& CxxReflection::instance()
	{
		/*	All registrations needs to done as constructor arguments,
		*	CxxMirror<...>({...register function/type pointers by name...})	*/
		static Reflection cxxMirror({

			/* Reflect is a builder calss, to provide type/pointers by names. Points to note -
			*  - Variable/Function pointers can only be passed to Reflect::build() function.
			*  - build function can only be called on objects returned by Reflect::variable() or Reflect::function().
			*  - if the function is global, not enclosed in any namespace, it can be registered as
			*		Reflect().function("function_name").build(..function_pointer..)
			*  - if the function is enclosed in a namespace, it can be registered as
			*		Reflect().namespace("namespace_name").function("function_name").build(_function_pointer_).
			*/
			Reflect().nameSpace("book").function("addBookInfo").build(book::addBookInfo),
			Reflect().nameSpace("book").function("showBookInfo").build(book::showBookInfo),
			Reflect().nameSpace("person").function("setProfile").build(person::setProfile),
			Reflect().nameSpace("person").function("showProfile").build(person::showProfile),

			/*
			*  - if the its a member function, it can be registered as
			*		Reflect().record("class/struct/union_name").function("function_name").build(_function_pointer_).
			*/
			Reflect().nameSpace("test_project").record("Date").constructor<Date>().build()


			/*
			*  - if the its a member function and enclosed in a namespace, it can be registered as
			*		Reflect().nameSpace("namespace_name").record("class/struct/union_name").function("function_name").build(_function_pointer_).
			*/

			});

		//cxxMirror object created statically, so thread safe.
		return cxxMirror;
	}
}