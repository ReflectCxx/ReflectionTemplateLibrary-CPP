#include "Reflection.h"
#include "Reflect.hpp"

//User defined types to be reflected.
#include "Complex.h"
#include "Date.h"
#include "Book.h"

using namespace std;
using namespace nsdate;
using namespace rtl::access;
using namespace rtl::builder;

CxxMirror& MyReflection::instance()
{
	static CxxMirror cxxMirror({

		//Global function, not contained in any namespace.
		Reflect().function("getComplexNumAsString").build(getComplexNumAsString),
		Reflect().function<std::string>("reverseString").build(reverseString),
		Reflect().function<const char*>("reverseString").build(reverseString),

		//Global functions, in "complex" namespace.
		Reflect().nameSpace("complex").function("setReal").build(complex::setReal),
		Reflect().nameSpace("complex").function("setImaginary").build(complex::setImaginary),
		Reflect().nameSpace("complex").function("getMagnitude").build(complex::getMagnitude),

		//"Date" struct, in test_project namespace. Ctor, Date()
		Reflect().nameSpace("nsdate").record("Date").constructor<Date>().build(),
		//Ctor, Date(std::string)
		Reflect().nameSpace("nsdate").record("Date").constructor<Date>().build<string>(),
		//Ctor, Date(unsigned, unsigned, unsigned)
		Reflect().nameSpace("nsdate").record("Date").constructor<Date>().build<unsigned, unsigned, unsigned>(),

		//class Book, no namespace. constructors builds.
		Reflect().record("Book").constructor<Book>().build(),
		Reflect().record("Book").constructor<Book>().build<double, string>(),

		////class Book, Methods
		//Reflect().record("Book").function("getPublishedOn").build(&Book::getPublishedOn),
		////Overloaded Methods
		//Reflect().record("Book").function("updateBookInfo").build(&Book::updateBookInfo)
	});

	return cxxMirror;
}