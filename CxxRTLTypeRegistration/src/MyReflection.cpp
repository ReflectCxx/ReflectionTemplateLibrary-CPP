
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

namespace the_reflection
{
    CxxMirror& cxx::mirror()
    {
        static CxxMirror cxxMirror = CxxMirror(
        {
        /*  ---------------------------------
            Registering pod & few STL types.
            ---------------------------------  */

        //  Registering void, valid but not useful at all.
            Reflect().nameSpace().record<void>("void").build(),

        //  Registering type 'void' again, ignored & emits-
        //  [WARNING] Multiple registrations of the same type detected.
            Reflect().nameSpace().record<void>("void").build(),

        //  Registering type 'void' again, but with different name. ignored & emits-
        //  [WARNING] Multiple registrations of the same type detected.
            Reflect().nameSpace().record<void>("ccvoid").build(),

        //  Registering pod, reflecting- constructor, copy-constructor & destructor.
            Reflect().nameSpace().record<char>("char").build(),

            Reflect().nameSpace("std").record<std::string_view>("string_view").build(),

        //  Registers std::string class
            Reflect().member<std::string>().methodConst("empty").build(&std::string::empty),

        /*  Attempting to register the same type(`std::string`) again under a different name.
        *   RTL will ignore this duplicate registration and retain the first one. Emits a warning on the console:
        *   "[WARNING] Multiple registrations of the same type with different names detected."
        */  Reflect().member<std::string>().methodConst("empty").build(&std::string::empty),

            Reflect().nameSpace("std").record<std::string>("string").build(),

        /*  Attempting to register std::string_view, but the provided member function pointer belongs to std::string.
        *   RTL will ignore this registration. Emits a warning on the console:
        *   "[WARNING] Member function pointer does not belong to the class being registered!"
        */  Reflect().member<std::string_view>().methodConst("empty").build(&std::string::empty),

        ////  Finally, register std::string_view with correct member-function-pointer
        //    Reflect().nameSpace("ccstd").record<std::string_view>().methodConst("empty").build(&std::string_view::empty),

        //  Finally, register std::string_view with correct member-function-pointer
            Reflect().member<std::string_view>().methodConst("empty").build(&std::string_view::empty),


        /*  -----------------------------------------------------------------
            Registering global, C-like functions, with & without namespaces.
            -----------------------------------------------------------------  */

        //  Function taking no arguments. '<void>' must be specified if other overload exists else not needed. compiler error otherwise.
            Reflect().nameSpace().function<void>(str_reverseString).build(reverseString),

        //  Overloaded function, takes 'string' arguments. '<string>' must be specified as template parameter.
            Reflect().nameSpace().function<string>(str_reverseString).build(reverseString),

        //  Overloaded function, takes 'const char*' arguments.
            Reflect().nameSpace().function<const char*>(str_reverseString).build(reverseString),

        //  Unique function, no overloads, no need to specify signature as template parameters.
            Reflect().nameSpace().function(str_getComplexNumAsString).build(getComplexNumAsString),

        /*  Grouping functions under a namespace, which is optional. they can be registered without it as well.
            but if registered under namspace, then to retrieve it from CxxMirror object, namespace name must be passed,
            e.g. cxx::mirror().getFunction("namespace_name", "function_name") & cxx::mirror().getRecord("namespace_name", "record_name")
        */  Reflect().nameSpace(str_complex).function(str_setReal).build(complex::setReal),
            Reflect().nameSpace(str_complex).function(str_setImaginary).build(complex::setImaginary),
            Reflect().nameSpace(str_complex).function(str_getMagnitude).build(complex::getMagnitude),


        /*  -----------------------------------------------------------------------------------------------------------
            Registering user defined types. class/struct- generally termed as 'Record' as per LLVM's naming convention
            -----------------------------------------------------------------------------------------------------------  */

        //  Constructors registration, class/struct name and type must be passed 'record<TYPE>("NAME")'.
        //  Registers default constructor with implicit registration of destructor & copy-constructor.
            Reflect().nameSpace(date::ns).record<nsdate::Date>(date::struct_).build(),

        //  Overloaded constructor, taking 'string' as argument, signature must be specified as template parameter.
            Reflect().member<nsdate::Date>().constructor<string>().build(),

        //  Again, register an overloaded constructor with diffeent signature.
            Reflect().member<nsdate::Date>().constructor<unsigned, unsigned, unsigned>().build(),
        
        //  Registring, Unique method, no overloads. Taking param 'std::string', auto deduced via function-pointer.
            Reflect().member<nsdate::Date>().method(date::str_updateDate).build(&nsdate::Date::updateDate),
        
        //  Registring const-method, 'methodConst()' function must be used. compiler error otherwise.
            Reflect().member<nsdate::Date>().methodConst(date::str_getAsString).build(&nsdate::Date::getAsString),
        
        //  Registring static-method, 'methodStatic()' function must be used. compiler error otherwise.
            Reflect().member<nsdate::Calender>().methodStatic(calender::str_create).build(&nsdate::Calender::create),
        
        //  Registring unique methods of class Calender, no overloads.
            Reflect().member<nsdate::Calender>().method(calender::str_getTheEvent).build(&nsdate::Calender::getTheEvent),
            Reflect().member<nsdate::Calender>().method(calender::str_getTheDate).build(&nsdate::Calender::getTheDate),
            Reflect().member<nsdate::Calender>().method(calender::str_getSavedEvent).build(&nsdate::Calender::getSavedEvent),
            Reflect().member<nsdate::Calender>().method(calender::str_getSavedDate).build(&nsdate::Calender::getSavedDate),

        //  class Calender, registering after the methods. (order doesn't matter)
            Reflect().nameSpace(date::ns).record<nsdate::Calender>(calender::struct_).build(),

        //  Registering 'Event' for reflection; instance creation fails since its default constructor is private or deleted.
        //  At least one member must be registered for RTL to recognize the type. be it property, member-function or constructor.
            Reflect().nameSpace(event::ns).record<nsdate::Event>(event::struct_).build(),
            Reflect().member<nsdate::Event>().method(event::str_reset).build(&nsdate::Event::reset),

        //  Registering Library's constructor. Stack allocation (rtl::alloc::Stack) will fail since its copy constructor is deleted 
        //  and its required by 'std::any' to store its object via copy-construction. But instance on heap (rtl::alloc::HEAP) can be
        //  constructed since, in that case, 'std::any' stores only the poiner which does not requires copy constructor to be called.
            Reflect().nameSpace().record<Library>(library::class_).build(),
        
        //  Registring static-method, 'methodStatic()' function must be used. compiler error otherwise.
            Reflect().member<Library>().methodStatic(library::str_addBook).build(&Library::addBook),
            Reflect().member<Library>().methodStatic(library::str_getBookByTitle).build(&Library::getBookByTitle),

        //  class 'Book', methods & constructors.
        //  Registering default constructor.
            Reflect().nameSpace().record<Book>(book::class_).build(),
        
        //  Registering overloaded constructor, signature must be specified as template parameter.
            Reflect().member<Book>().constructor<double, string>().build(),
        
        //  Unique methods, no overloads.
            Reflect().member<Book>().method(book::str_setAuthor).build(&Book::setAuthor),
        
        //  Unique method, taking 'std::string' & 'const std::string&' as argument, auto deduced via function-pointer.
            Reflect().member<Book>().method(book::str_addPreface).build(&Book::addPreface),
        
        //  Furthur registrations of unique-menthods, signature auto-deduced via function pointer.
            Reflect().member<Book>().method(book::str_setDescription).build(&Book::setDescription),
            Reflect().member<Book>().method(book::str_getPublishedOn).build(&Book::getPublishedOn),
            Reflect().member<Book>().method(book::str_addCopyrightTag).build(&Book::addCopyrightTag),

        //  Registering overloaded methods, signature must be specified as template params since other overloads exists, else compiler error.
            Reflect().member<Book>().method<void>(book::str_updateBookInfo).build(&Book::updateBookInfo),
            Reflect().member<Book>().method<const char*, double, string>(book::str_updateBookInfo).build(&Book::updateBookInfo),
            Reflect().member<Book>().method<string, double, const char*>(book::str_updateBookInfo).build(&Book::updateBookInfo),

        //  class 'Person', methods & constructors.
            Reflect().nameSpace().record<Person>(person::class_).build(),
            Reflect().member<Person>().constructor<string>().build(),
            Reflect().member<Person>().methodStatic(person::str_createPtr).build(&Person::createPtr),
            Reflect().member<Person>().method<void>(person::str_updateAddress).build(&Person::updateAddress),
            Reflect().member<Person>().method<string>(person::str_updateAddress).build(&Person::updateAddress),
            Reflect().member<Person>().method(person::str_getFirstName).build(&Person::getFirstName),

        //  Registring const-method, 'methodConst()' function must be used. compiler error otherwise.
            Reflect().member<Person>().methodConst(person::str_updateLastName).build(&Person::updateLastName),

        //  Registring const-method overload, non-const overloaded method already registered above.
            Reflect().member<Person>().methodConst<void>(person::str_updateAddress).build(&Person::updateAddress),
            Reflect().member<Person>().methodConst<string>(person::str_updateAddress).build(&Person::updateAddress),
            Reflect().member<Person>().methodStatic(person::str_getDefaults).build(&Person::getDefaults),
            Reflect().member<Person>().methodStatic(person::str_createConst).build(&Person::createConst),
            Reflect().member<Person>().methodStatic<void>(person::str_getProfile).build(&Person::getProfile),
            Reflect().member<Person>().methodStatic<bool>(person::str_getProfile).build(&Person::getProfile),
            Reflect().member<Person>().methodStatic<string, size_t>(person::str_getProfile).build(&Person::getProfile),

        //  class 'Animal', methods & constructors.
            Reflect().nameSpace().record<Animal>(animal::class_).build(),
            Reflect().member<Animal>().constructor<string>().build(),  //overloaded constructor.
            Reflect().member<Animal>().method(animal::str_setFamilyName).build(&Animal::setFamilyName),  //unique method, no overloads.
            
        //  Unique const-method, no overloads.
            Reflect().member<Animal>().methodConst(animal::str_getFamilyName).build(&Animal::getFamilyName),
        
        //  Overloaded method, taking const-ref as argument.
            Reflect().member<Animal>().method<const std::string&>(animal::str_setAnimalName).build(&Animal::setAnimalName),
        
        //  Static method, taking const-ref as argument.
            Reflect().member<Animal>().methodStatic<const std::string&>(animal::str_updateZooKeeper).build(&Animal::updateZooKeeper),

            #if defined(__GNUC__) && !defined(__clang__)
            /*  GCC fails to automatically identify the correct overloaded functor to pick. (non-const-lvalue-ref & rvalue as argument)
                we need to explicitly cast the functor like, static_cast<void(Animal::*)(std::string&)>(&Animal::setAnimalName).
            */  Reflect().record<Animal>()
                         .method<std::string&>(animal::str_setAnimalName)
                         .build(static_cast<void(Animal::*)(std::string&)>(&Animal::setAnimalName)),  //overloaded method, taking non-const lvalue reference as argument.
                
                Reflect().record<Animal>()
                         .method<std::string&&>(animal::str_setAnimalName)
                         .build(static_cast<void(Animal::*)(std::string&&)>(&Animal::setAnimalName)),  //overloaded method, taking rvalue reference as argument.
                
                Reflect().record<Animal>()
                         .methodStatic<std::string&>(animal::str_updateZooKeeper)
                         .build(static_cast<std::string(*)(std::string&)>(&Animal::updateZooKeeper)),  //static method, taking non-const lvalue reference as argument.
                
                Reflect().record<Animal>()
                         .methodStatic<std::string&&>(animal::str_updateZooKeeper)
                         .build(static_cast<std::string(*)(std::string&&)>(&Animal::updateZooKeeper)), //static method, taking rvalue reference as argument.
            #else
                Reflect().member<Animal>()
                         .method<std::string&>(animal::str_setAnimalName)
                         .build(&Animal::setAnimalName),  //overloaded method, taking non-const lvalue reference as argument.
                
                Reflect().member<Animal>()
                         .method<std::string&&>(animal::str_setAnimalName)
                         .build(&Animal::setAnimalName),  //overloaded method, taking rvalue reference as argument.
                
                Reflect().member<Animal>()
                         .methodStatic<std::string&>(animal::str_updateZooKeeper)
                         .build(&Animal::updateZooKeeper),  //static method, taking non-const lvalue reference as argument.
                
                Reflect().member<Animal>()
                         .methodStatic<std::string&&>(animal::str_updateZooKeeper)
                         .build(&Animal::updateZooKeeper), //static method, taking rvalue reference as argument.
            #endif
        });

        static const auto _ = [&]()
        {
            const std::string pathStr = std::filesystem::current_path().string() + "/MyReflection.json";
            rtl::CxxMirrorToJson::dump(cxxMirror, pathStr);
            return -1;
        }();

        return cxxMirror;
    }
}



namespace the_reflection
{
    //Optional setup for accessing registered types via unique-ids.
    std::size_t reflected_id::book = rtl::detail::TypeId<Book>::get();
    std::size_t reflected_id::person = rtl::detail::TypeId<Person>::get();
    std::size_t reflected_id::animal = rtl::detail::TypeId<Animal>::get();
    std::size_t reflected_id::library = rtl::detail::TypeId<Library>::get();

    std::size_t reflected_id::date = rtl::detail::TypeId<nsdate::Date>::get();
    std::size_t reflected_id::event = rtl::detail::TypeId<nsdate::Event>::get();
    std::size_t reflected_id::calender = rtl::detail::TypeId<nsdate::Calender>::get();

    std::size_t reflected_id::void_t = rtl::detail::TypeId<void>::get();
    std::size_t reflected_id::char_t = rtl::detail::TypeId<char>::get();
    std::size_t reflected_id::std_string = rtl::detail::TypeId<std::string>::get();
    std::size_t reflected_id::std_string_view = rtl::detail::TypeId<std::string_view>::get();

    //Optional setup - mapping unique-ids to string type-names (for Testing-Purposes only).
    const std::size_t reflected_id::getRecordIdFor(const std::string& pRecordName)
    {
        static std::unordered_map<std::string, std::size_t> nameIdMap(
        {
            { "char", char_t },
            { "void", void_t },
            { "string", std_string },
            { "string_view", std_string_view },

            { book::class_, book },
            { date::struct_, date },
            { event::struct_, event },
            { animal::class_, animal },
            { person::class_, person },
            { library::class_, library },
            { calender::struct_, calender }
        });

        const auto& itr = nameIdMap.find(pRecordName);
        return (itr == nameIdMap.end() ? rtl::index_none:itr->second);
    }
}