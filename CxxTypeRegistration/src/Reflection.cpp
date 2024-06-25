#include "Reflection.h"
#include "Reflect.hpp"

//User defined types to be reflected.
#include "Date.h"
#include "Book.h"
#include "Complex.h"

using namespace std;
using namespace test_utils;
using namespace rtl::access;
using namespace rtl::builder;

CxxMirror& MyReflection::instance()
{
	static CxxMirror cxxMirror({

		//Global function, not contained in any namespace.
		//No need to specify "function<>" template types, since its the unique function, no overloads.
		Reflect().function(str_getComplexNumAsString).build(getComplexNumAsString),

		//Overloads, Specify the overload signature as template in "function<_signature...>"
		//if one of the function takes zero params, <void> must be used, else complie error.
		Reflect().function<void>(str_reverseString).build(reverseString),
		Reflect().function<std::string>(str_reverseString).build(reverseString),
		Reflect().function<const char*>(str_reverseString).build(reverseString),

		//Global functions, in "complex" namespace.
		Reflect().nameSpace(str_complex).function(str_setReal).build(complex::setReal),
		Reflect().nameSpace(str_complex).function(str_setImaginary).build(complex::setImaginary),
		Reflect().nameSpace(str_complex).function(str_getMagnitude).build(complex::getMagnitude),

		//date::record struct, in nsdate namespace. Ctor, Date()
		Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor().build(),

		//Ctor, Date(std::string)
		Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor<string>().build(),

		//Ctor, Date(unsigned, unsigned, unsigned)
		Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor<unsigned, unsigned, unsigned>().build(),

		//class Book, no namespace. constructors builds.
		Reflect().record<Book>(book::class_).constructor().build(),
		Reflect().record<Book>(book::class_).constructor<double, string>().build(),

		//class Book, Methods
		Reflect().record<Book>(book::class_).method(book::str_getPublishedOn).build(&Book::getPublishedOn)

		//Overloaded Methods
		//Reflect().record<Book>("Book").method("updateBookInfo").build(&Book::updateBookInfo)
	});

	return cxxMirror;
}