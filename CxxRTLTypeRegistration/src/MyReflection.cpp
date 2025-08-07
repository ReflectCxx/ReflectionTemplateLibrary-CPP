
#include <filesystem>

#include "MyReflection.h"
#include "CxxMirrorToJson.h"

//User defined types to be reflected.
#include "Date.h"
#include "Book.h"
#include "Person.h"
#include "Complex.h"
#include "Animal.h"
#include "Library.h"

/*
TestUtils, provides the interface to test/compare reflected type objects with actual objects (created via strict typing)
without exposing the actual type objects to "CxxReflectionTests" project.*/
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsPerson.h"
#include "TestUtilsAnimal.h"
#include "GlobalTestUtils.h"


using namespace std;
using namespace test_utils;
using namespace rtl::access;
using namespace rtl::builder;

CxxMirror& MyReflection::instance()
{
    static CxxMirror cxxMirror = CxxMirror(
    {
    //  Registers std::string class, but no constructor.
        Reflect().nameSpace("std").record<std::string>("string").methodConst("empty").build(&std::string::empty),

    /*  Attempting to register the same type(`std::string`) again under a different name.
    *   RTL will ignore this duplicate registration and retain the first one. Emits a warning on the console:
    *   "[WARNING] Multiple registrations of the same type with different names detected."
    */  Reflect().nameSpace("std").record<std::string>("std_string").methodConst("empty").build(&std::string::empty),

    /*  Attempting to register std::string_view, but the provided member function pointer belongs to std::string.
    *   RTL will ignore this registration. Emits a warning on the console:
    *   "[WARNING] Member function pointer does not belong to the class being registered!"
    */  Reflect().nameSpace("std").record<std::string_view>("string_view").methodConst("empty").build(&std::string::empty),

    //  Finally, register std::string_view with correct member-function-pointer
        Reflect().nameSpace("std").record<std::string_view>("string_view").methodConst("empty").build(&std::string_view::empty),

    //  Registering user defined-types.
    //  global functions, not contained in any namespace.
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
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor().build(),  //registers default constructor
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor<string>().build(),  //overloaded constructor, taking 'string' as argument, must be specified as template param.
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).constructor<unsigned, unsigned, unsigned>().build(),  //again, the overloaded constructor.
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).method(date::str_updateDate).build(&nsdate::Date::updateDate),  //unique method, no overloads.
        Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).methodConst(date::str_getAsString).build(&nsdate::Date::getAsString),  //const method registration, 'methodConst()' function must be used. compiler error otherwise.

        //class Calender, default constructor.
        Reflect().nameSpace(calender::ns).record<nsdate::Calender>(calender::struct_).constructor().build(),
        Reflect().nameSpace(calender::ns).record<nsdate::Calender>(calender::struct_).methodStatic(calender::str_create).build(&nsdate::Calender::create),
        Reflect().nameSpace(calender::ns).record<nsdate::Calender>(calender::struct_).method(calender::str_getTheEvent).build(&nsdate::Calender::getTheEvent),  //unique method, no overloads.
        Reflect().nameSpace(calender::ns).record<nsdate::Calender>(calender::struct_).method(calender::str_getTheDate).build(&nsdate::Calender::getTheDate),  //unique method, no overloads.
        Reflect().nameSpace(calender::ns).record<nsdate::Calender>(calender::struct_).method(calender::str_getSavedEvent).build(&nsdate::Calender::getSavedEvent),  //unique method, no overloads.
        Reflect().nameSpace(calender::ns).record<nsdate::Calender>(calender::struct_).method(calender::str_getSavedDate).build(&nsdate::Calender::getSavedDate),  //unique method, no overloads.

        // Registers 'Event' for reflection; instance creation fails since its default constructor is private or deleted.
        // At least one member must be registered for RTL to recognize the type. be it property, member-function or constructor.
        Reflect().nameSpace(event::ns).record<nsdate::Event>(event::struct_).constructor().build(),

        // Registers Library's constructor; stack allocation (rtl::alloc::Stack) will fail since its copy constructor is deleted.
        Reflect().record<Library>(library::class_).constructor().build(),   //can only construct instance on heap (rtl::alloc::HEAP) via RTL.
        Reflect().record<Library>(library::class_).methodStatic(library::str_addBook).build(&Library::addBook),  //Static method registration, 'methodStatic()' function must be used. compiler error otherwise.
        Reflect().record<Library>(library::class_).methodStatic(library::str_getBookByTitle).build(&Library::getBookByTitle),

        //class 'Book', methods & constructors.
        Reflect().record<Book>(book::class_).constructor().build(),     //registers default constructor.
        Reflect().record<Book>(book::class_).constructor<double, string>().build(),
        Reflect().record<Book>(book::class_).method(book::str_setAuthor).build(&Book::setAuthor),  //unique methods, no overloads.
        Reflect().record<Book>(book::class_).method(book::str_addPreface).build(&Book::addPreface),  //method, taking 'std::string' & 'const std::string&' as argument.
        Reflect().record<Book>(book::class_).method(book::str_setDescription).build(&Book::setDescription),
        Reflect().record<Book>(book::class_).method(book::str_getPublishedOn).build(&Book::getPublishedOn),
        Reflect().record<Book>(book::class_).method(book::str_addCopyrightTag).build(&Book::addCopyrightTag),  //method, taking 'const std::string' as argument.
        Reflect().record<Book>(book::class_).method<void>(book::str_updateBookInfo).build(&Book::updateBookInfo),  //method overloading, '<void>' must be specified since other overloads exists.
        Reflect().record<Book>(book::class_).method<const char*, double, string>(book::str_updateBookInfo).build(&Book::updateBookInfo),	
        Reflect().record<Book>(book::class_).method<string, double, const char*>(book::str_updateBookInfo).build(&Book::updateBookInfo),

        //class 'Person', methods & constructors.
        Reflect().record<Person>(person::class_).constructor().build(),     //registers default constructor.
        Reflect().record<Person>(person::class_).constructor<string>().build(),
        Reflect().record<Person>(person::class_).methodStatic(person::str_createPtr).build(&Person::createPtr),
        Reflect().record<Person>(person::class_).method<void>(person::str_updateAddress).build(&Person::updateAddress),
        Reflect().record<Person>(person::class_).method<string>(person::str_updateAddress).build(&Person::updateAddress),
        Reflect().record<Person>(person::class_).method(person::str_getFirstName).build(&Person::getFirstName),
        Reflect().record<Person>(person::class_).methodConst(person::str_updateLastName).build(&Person::updateLastName),  //const method registration, 'methodConst()' function must be used. compiler error otherwise.
        Reflect().record<Person>(person::class_).methodConst<void>(person::str_updateAddress).build(&Person::updateAddress),
        Reflect().record<Person>(person::class_).methodConst<string>(person::str_updateAddress).build(&Person::updateAddress),  //overloaded method based on 'const'.
        Reflect().record<Person>(person::class_).methodStatic(person::str_getDefaults).build(&Person::getDefaults),
        Reflect().record<Person>(person::class_).methodStatic(person::str_createConst).build(&Person::createConst),
        Reflect().record<Person>(person::class_).methodStatic<void>(person::str_getProfile).build(&Person::getProfile),
        Reflect().record<Person>(person::class_).methodStatic<bool>(person::str_getProfile).build(&Person::getProfile),
        Reflect().record<Person>(person::class_).methodStatic<string, size_t>(person::str_getProfile).build(&Person::getProfile),

        //class 'Animal', methods & constructors.
        Reflect().record<Animal>(animal::class_).constructor().build(),  //registers default constructor.
        Reflect().record<Animal>(animal::class_).constructor<string>().build(),  //overloaded constructor, taking 'string' as argument.
        Reflect().record<Animal>(animal::class_).method(animal::str_setFamilyName).build(&Animal::setFamilyName),  //unique method, no overloads.
        Reflect().record<Animal>(animal::class_).methodConst(animal::str_getFamilyName).build(&Animal::getFamilyName),  //unique const-method, no overloads.
        Reflect().record<Animal>(animal::class_).method<const std::string&>(animal::str_setAnimalName).build(&Animal::setAnimalName),  //overloaded method, taking const-ref as argument.
        Reflect().record<Animal>(animal::class_).methodStatic<const std::string&>(animal::str_updateZooKeeper).build(&Animal::updateZooKeeper),  //static method, taking const-ref as argument.

        #if defined(__GNUC__) && !defined(__clang__)
        /*  GCC fails to automatically identify the correct overloaded functor (method) to pick. (non-const-lvalue-ref & rvalue as argument)
            we need to explicitly cast the functor like, static_cast<void(Animal::*)(std::string&)>(&Animal::setAnimalName).
        */  Reflect().record<Animal>(animal::class_).method<std::string&>(animal::str_setAnimalName).build(static_cast<void(Animal::*)(std::string&)>(&Animal::setAnimalName)),  //overloaded method, taking non-const lvalue reference as argument.
            Reflect().record<Animal>(animal::class_).method<std::string&&>(animal::str_setAnimalName).build(static_cast<void(Animal::*)(std::string&&)>(&Animal::setAnimalName)),  //overloaded method, taking rvalue reference as argument.
            Reflect().record<Animal>(animal::class_).methodStatic<std::string&>(animal::str_updateZooKeeper).build(static_cast<std::string(*)(std::string&)>(&Animal::updateZooKeeper)),  //static method, taking non-const lvalue reference as argument.
            Reflect().record<Animal>(animal::class_).methodStatic<std::string&&>(animal::str_updateZooKeeper).build(static_cast<std::string(*)(std::string&&)>(&Animal::updateZooKeeper)), //static method, taking rvalue reference as argument.
        #else
            Reflect().record<Animal>(animal::class_).method<std::string&>(animal::str_setAnimalName).build(&Animal::setAnimalName),  //overloaded method, taking non-const lvalue reference as argument.
            Reflect().record<Animal>(animal::class_).method<std::string&&>(animal::str_setAnimalName).build(&Animal::setAnimalName),  //overloaded method, taking rvalue reference as argument.
            Reflect().record<Animal>(animal::class_).methodStatic<std::string&>(animal::str_updateZooKeeper).build(&Animal::updateZooKeeper),  //static method, taking non-const lvalue reference as argument.
            Reflect().record<Animal>(animal::class_).methodStatic<std::string&&>(animal::str_updateZooKeeper).build(&Animal::updateZooKeeper), //static method, taking rvalue reference as argument.
        #endif
    });

    static const auto _= [&]()
    {
        const std::string pathStr = std::filesystem::current_path().string() + "/MyReflection.json";
        rtl::CxxMirrorToJson::dump(cxxMirror, pathStr);
        return -1;
    }();

    return cxxMirror;
}
