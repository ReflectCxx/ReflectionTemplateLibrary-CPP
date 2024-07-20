
#include <filesystem>

#include "MyReflection.h"
#include "CxxMirrorToJson.h"

//User defined types to be reflected.
#include "Date.h"
#include "Book.h"
#include "Person.h"
#include "Complex.h"

/*
TestUtils, provides the interface to test/compare reflected type objects with actual objects (created via strict typing)
without exposing the actual type objects to "CxxReflectionTests" project.*/
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsPerson.h"
#include "TestUtilsGlobals.h"


using namespace std;
using namespace test_utils;
using namespace rtl::access;
using namespace rtl::builder;

CxxMirror& MyReflection::instance()
{
    static CxxMirror cxxMirror = CxxMirror({

        //global functions, not contained in any namespace.
        Reflect().function<void>(str_reverseString).build(reverseString),  //function taking no arguments. '<void>' must be specified if other overload exists else not needed. compiler error otherwise.
        Reflect().function<string>(str_reverseString).build(reverseString),  //overloaded function, takes 'string' arguments. '<string>' must be specified as template parameter.
        Reflect().function<const char*>(str_reverseString).build(reverseString),  //overloaded function, takes 'const char*' arguments.
        Reflect().function(str_getComplexNumAsString).build(getComplexNumAsString),  //unique function, no overloads, no need to specify signature as template parameters.

    /*  Grouping functions under a namespace, which is optional. they can be registered without it as well.
		but if registered under namspace, then to retrieve it from CxxMirror object, namespace name must be passed,
		ex - cxxMirror.getFunction("namespace_name", "function_name") & cxxMirror.getRecord("namespace_name", "record_name")
    */  Reflect().nameSpace(str_complex).function(str_setReal).build(complex::setReal),
        Reflect().nameSpace(str_complex).function(str_setImaginary).build(complex::setImaginary),
        Reflect().nameSpace(str_complex).function(str_getMagnitude).build(complex::getMagnitude),

        //Constructors registration, class/struct name and type must be passed 'record<TYPE>("NAME")'.
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor().build(),  //default constructor. Destructor gets registered automatically if any constructor is registered.
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor<string>().build(),  //overloaded constructor, taking 'string' as argument, must be specified as template param.
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor<unsigned, unsigned, unsigned>().build(),  //again, the overloaded constructor.
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor<nsdate::Date&>().build(),  //Copy constructor, taking non-const ref as argument.

        //class Calender, default constructor. Instances will always be created on heap and managed using shared_ptr.
        Reflect().nameSpace(calender::ns).record<nsdate::Calender>(calender::struct_).constructor().build(),
        Reflect().record<Library>(library::class_).methodStatic(library::str_addBook).build(&Library::addBook),  //Static method registration, 'methodStatic()' function must be used. compiler error otherwise.

        //class 'Book', methods & constructors.
        Reflect().record<Book>(book::class_).constructor().build(),
        Reflect().record<Book>(book::class_).constructor<const Book&>().build(),  //copy constructor, taking const-ref.
        Reflect().record<Book>(book::class_).constructor<double, string>().build(),
        Reflect().record<Book>(book::class_).method(book::str_setAuthor).build(&Book::setAuthor),  //unique methods, no overloads.
        Reflect().record<Book>(book::class_).method(book::str_setDescription).build(&Book::setDescription),
        Reflect().record<Book>(book::class_).method(book::str_getPublishedOn).build(&Book::getPublishedOn),
        Reflect().record<Book>(book::class_).method<void>(book::str_updateBookInfo).build(&Book::updateBookInfo),  //method overloading, '<void>' must be specified since other overloads exists.
        Reflect().record<Book>(book::class_).method<const char*, double, string>(book::str_updateBookInfo).build(&Book::updateBookInfo),	
        Reflect().record<Book>(book::class_).method<string, double, const char*>(book::str_updateBookInfo).build(&Book::updateBookInfo),

        //class 'Person', methods & constructors.
        Reflect().record<Person>(person::class_).constructor().build(),
        Reflect().record<Person>(person::class_).constructor<string>().build(),
        Reflect().record<Person>(person::class_).constructor<Person&>().build(),  //copy constructor taking non-const ref argument.
        Reflect().record<Person>(person::class_).constructor<const Person&>().build(),  //copy constructor taking const ref argument.
        Reflect().record<Person>(person::class_).method<void>(person::str_updateAddress).build(&Person::updateAddress),
        Reflect().record<Person>(person::class_).method<string>(person::str_updateAddress).build(&Person::updateAddress),
        Reflect().record<Person>(person::class_).methodConst(person::str_updateLastName).build(&Person::updateLastName),  //const method registration, 'methodConst()' function must be used. compiler error otherwise.
        Reflect().record<Person>(person::class_).methodConst<void>(person::str_updateAddress).build(&Person::updateAddress),
        Reflect().record<Person>(person::class_).methodConst<string>(person::str_updateAddress).build(&Person::updateAddress),  //overloaded method based on 'const'.
        Reflect().record<Person>(person::class_).methodStatic(person::str_getDefaults).build(&Person::getDefaults),
        Reflect().record<Person>(person::class_).methodStatic<void>(person::str_getProfile).build(&Person::getProfile),
        Reflect().record<Person>(person::class_).methodStatic<bool>(person::str_getProfile).build(&Person::getProfile),
        Reflect().record<Person>(person::class_).methodStatic<string, size_t>(person::str_getProfile).build(&Person::getProfile)
    });


    static bool dumped = false;
    if (!dumped) {
        const std::string pathStr = std::filesystem::current_path().string() + "/MyReflection.json";
        rtl::CxxMirrorToJson::dump(cxxMirror, pathStr);
        dumped = true;
    }

    return cxxMirror;
}