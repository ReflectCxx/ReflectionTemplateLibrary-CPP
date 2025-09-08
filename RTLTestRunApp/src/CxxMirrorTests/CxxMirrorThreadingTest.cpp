
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

#include "../../CxxTestProps/inc/Date.h"
#include "../../CxxTestProps/inc/Book.h"
#include "../../CxxTestProps/inc/Animal.h"
#include "../../CxxTestProps/inc/Person.h"
#include "../../CxxTestProps/inc/Library.h"
#include "../../CxxTestProps/inc/Complex.h"
#include "../MyReflectionTests/MyReflectingType.h"

#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsPerson.h"
#include "TestUtilsAnimal.h"
#include "GlobalTestUtils.h"

#include "RTLibInterface.h"
#include "CxxMirrorThreadingTest.h"

using namespace test_utils;

namespace rtl_tests
{
    void InitMirror::reflectingEvent()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().ns(event::ns).record<nsdate::Event>(event::struct_).build(),

            rtl::type().member<nsdate::Event>().method(event::str_reset).build(&nsdate::Event::reset),
        });

        std::cout << "\n  [t2]\trtl_tests::InitMirror::reflectingEvent() ==> Done.\n";
    }


    void InitMirror::reflectingLibrary()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().record<Library>(library::class_).build(),

            rtl::type().member<Library>().methodStatic(library::str_addBook).build(&Library::addBook),

            rtl::type().member<Library>().methodStatic(library::str_getBookByTitle).build(&Library::getBookByTitle)
        });

        std::cout << "\n  [t5]\trtl_tests::InitMirror::reflectingLibrary() ==> Done.\n";
    }


    void InitMirror::reflectingDate()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().ns(date::ns).record<nsdate::Date>(date::struct_).build(),

            rtl::type().member<nsdate::Date>().constructor<std::string>().build(),

            rtl::type().member<nsdate::Date>().constructor<unsigned, unsigned, unsigned>().build(),

            rtl::type().member<nsdate::Date>().method(date::str_updateDate).build(&nsdate::Date::updateDate),

            rtl::type().member<nsdate::Date>().methodConst(date::str_getAsString).build(&nsdate::Date::getAsString)
        });

        std::cout << "\n  [t1]\trtl_tests::InitMirror::reflectingDate() ==> Done.\n";
    }


    void InitMirror::reflectingCalender()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().ns(date::ns).record<nsdate::Calender>(calender::struct_).build(),

            rtl::type().member<nsdate::Calender>().methodStatic(calender::str_create).build(&nsdate::Calender::create),

            rtl::type().member<nsdate::Calender>().method(calender::str_getTheEvent).build(&nsdate::Calender::getTheEvent),

            rtl::type().member<nsdate::Calender>().method(calender::str_getTheDate).build(&nsdate::Calender::getTheDate),

            rtl::type().member<nsdate::Calender>().method(calender::str_getSavedEvent).build(&nsdate::Calender::getSavedEvent),

            rtl::type().member<nsdate::Calender>().method(calender::str_getSavedDate).build(&nsdate::Calender::getSavedDate)
        });

        std::cout << "\n  [t7]\trtl_tests::InitMirror::reflectingCalender() ==> Done.\n";
    }


    void InitMirror::reflectingPodsStl()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().function("strlen").build(std::strlen),

            rtl::type().record<char>("char").build(),

            rtl::type().record<std::vector<int>>("vector_int").build(),

            rtl::type().ns("std").record<std::string>("string").build(),

            rtl::type().ns("std").record<std::string_view>("string_view").build(),

            rtl::type().member<std::string>().methodConst("empty").build(&std::string::empty),

            rtl::type().member<std::string_view>().methodConst("empty").build(&std::string_view::empty),

            rtl::type().member<std::vector<int>>().methodConst("empty").build(&std::vector<int>::empty),

            rtl::type().member<std::vector<int>>().method<const int&>("push_back").build(&std::vector<int>::push_back)
        });

        std::cout << "\n  [t6]\trtl_tests::InitMirror::reflectingPodsStl() ==> Done.\n";
    }


    void InitMirror::reflectingCStyleFunctions()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().function<void>(str_reverseString).build(reverseString),

            rtl::type().function<std::string>(str_reverseString).build(reverseString),

            rtl::type().function<const char*>(str_reverseString).build(reverseString),

            rtl::type().function(str_getComplexNumAsString).build(getComplexNumAsString),

            rtl::type().ns(str_complex).function(str_setReal).build(complex::setReal),

            rtl::type().ns(str_complex).function(str_setImaginary).build(complex::setImaginary),

            rtl::type().ns(str_complex).function(str_getMagnitude).build(complex::getMagnitude),

            rtl::type().ns("ext").function("sendString").build(my_type::ext::sendString),

            rtl::type().ns("ext").function<const char*>("sendAsString").build(my_type::ext::sendAsString),

            rtl::type().ns("ext").function<my_type::Person>("sendAsString").build(my_type::ext::sendAsString),

            rtl::type().ns("ext").function<my_type::Person&&>("sendAsString").build(my_type::ext::sendAsString)
        });

        std::cout << "\n  [t9]\trtl_tests::InitMirror::reflectingCStyleFunctions() ==> Done.\n";
    }


    void InitMirror::reflectingBook()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().record<Book>(book::class_).build(),

            rtl::type().member<Book>().constructor<double, std::string>().build(),

            rtl::type().member<Book>().method(book::str_setAuthor).build(&Book::setAuthor),

            rtl::type().member<Book>().method(book::str_addPreface).build(&Book::addPreface),

            rtl::type().member<Book>().method(book::str_setDescription).build(&Book::setDescription),
            
            rtl::type().member<Book>().method(book::str_getPublishedOn).build(&Book::getPublishedOn),
            
            rtl::type().member<Book>().method(book::str_addCopyrightTag).build(&Book::addCopyrightTag),

            rtl::type().member<Book>().method<void>(book::str_updateBookInfo).build(&Book::updateBookInfo),
            
            rtl::type().member<Book>().method<const char*, double, std::string>(book::str_updateBookInfo).build(&Book::updateBookInfo),
            
            rtl::type().member<Book>().method<std::string, double, const char*>(book::str_updateBookInfo).build(&Book::updateBookInfo)
        });

        std::cout << "\n  [t0]\trtl_tests::InitMirror::reflectingBook() ==> Done.\n";
    }


    void InitMirror::reflectingMyTypePerson()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().record<my_type::Person>("Person").build(),

            rtl::type().member<my_type::Person>().constructor<std::string>().build(),

            rtl::type().member<my_type::Person>().method("getName").build(&my_type::Person::getName),

            rtl::type().member<my_type::Person>().methodStatic("getDefaults").build(&my_type::Person::getDefaults),

            rtl::type().member<my_type::Person>().method("updateAddress").build(&my_type::Person::updateAddress),

            rtl::type().member<my_type::Person>().methodConst("updateAddress").build(&my_type::Person::updateAddress),

            rtl::type().member<my_type::Person>().method("setTitle").build(&my_type::Person::setTitle),

            rtl::type().member<my_type::Person>().method<std::string&&>("setOccupation").build(&my_type::Person::setOccupation),

            rtl::type().member<my_type::Person>().method<const std::string&>("setOccupation").build(&my_type::Person::setOccupation),

            rtl::type().member<my_type::Person>().method<std::string>("setProfile").build(&my_type::Person::setProfile),

            rtl::type().member<my_type::Person>().method<std::string&>("setProfile").build(&my_type::Person::setProfile),

            rtl::type().member<my_type::Person>().methodConst("getProfile").build(&my_type::Person::getProfile)
        });

        std::cout << "\n  [t8]\trtl_tests::InitMirror::reflectingMyTypePerson() ==> Done.\n";
    }


    void InitMirror::reflectingPerson()
    {
        auto _ = rtl::CxxMirror({

            rtl::type().record<Person>(person::class_).build(),

            rtl::type().member<Person>().constructor<std::string>().build(),

            rtl::type().member<Person>().methodStatic(person::str_createPtr).build(&Person::createPtr),

            rtl::type().member<Person>().method<void>(person::str_updateAddress).build(&Person::updateAddress),

            rtl::type().member<Person>().method<std::string>(person::str_updateAddress).build(&Person::updateAddress),

            rtl::type().member<Person>().method(person::str_getFirstName).build(&Person::getFirstName),

            rtl::type().member<Person>().methodConst(person::str_updateLastName).build(&Person::updateLastName),

            rtl::type().member<Person>().methodConst<void>(person::str_updateAddress).build(&Person::updateAddress),

            rtl::type().member<Person>().methodConst<std::string>(person::str_updateAddress).build(&Person::updateAddress),

            rtl::type().member<Person>().methodStatic(person::str_getDefaults).build(&Person::getDefaults),

            rtl::type().member<Person>().methodStatic(person::str_createConst).build(&Person::createConst),

            rtl::type().member<Person>().methodStatic<void>(person::str_getProfile).build(&Person::getProfile),

            rtl::type().member<Person>().methodStatic<bool>(person::str_getProfile).build(&Person::getProfile),

            rtl::type().member<Person>().methodStatic<std::string, size_t>(person::str_getProfile).build(&Person::getProfile)
        });

        std::cout << "\n  [t4]\trtl_tests::InitMirror::reflectingPerson() ==> Done.\n";
    }


    void InitMirror::reflectingAnimal()
    {
        auto _ = rtl::CxxMirror({
            
            rtl::type().record<Animal>(animal::class_).build(),

            rtl::type().member<Animal>().constructor<std::string>().build(),

            rtl::type().member<Animal>().method(animal::str_setFamilyName).build(&Animal::setFamilyName),

            rtl::type().member<Animal>().methodConst(animal::str_getFamilyName).build(&Animal::getFamilyName),

            rtl::type().member<Animal>().method<const std::string&>(animal::str_setAnimalName).build(&Animal::setAnimalName),

            rtl::type().member<Animal>().methodStatic<const std::string&>(animal::str_updateZooKeeper).build(&Animal::updateZooKeeper),

            #if defined(__GNUC__) && !defined(__clang__)
            /*  GCC fails to automatically identify the correct overloaded functor to pick. (non-const-lvalue-ref & rvalue as argument)
                we need to explicitly cast the functor like, static_cast<void(Animal::*)(std::string&)>(&Animal::setAnimalName).
            */  rtl::type().member<Animal>()
                           .method<std::string&>(animal::str_setAnimalName)
                           .build(static_cast<void(Animal::*)(std::string&)>(&Animal::setAnimalName)),  //overloaded method, taking non-const lvalue reference as argument.

                rtl::type().member<Animal>()
                           .method<std::string&&>(animal::str_setAnimalName)
                           .build(static_cast<void(Animal::*)(std::string&&)>(&Animal::setAnimalName)),  //overloaded method, taking rvalue reference as argument.

                rtl::type().member<Animal>()
                           .methodStatic<std::string&>(animal::str_updateZooKeeper)
                           .build(static_cast<std::string(*)(std::string&)>(&Animal::updateZooKeeper)),  //static method, taking non-const lvalue reference as argument.

                rtl::type().member<Animal>()
                           .methodStatic<std::string&&>(animal::str_updateZooKeeper)
                           .build(static_cast<std::string(*)(std::string&&)>(&Animal::updateZooKeeper)), //static method, taking rvalue reference as argument.
            #else
                rtl::type().member<Animal>()
                           .method<std::string&>(animal::str_setAnimalName)
                           .build(&Animal::setAnimalName),

                rtl::type().member<Animal>()
                           .method<std::string&&>(animal::str_setAnimalName)
                           .build(&Animal::setAnimalName),

                rtl::type().member<Animal>()
                           .methodStatic<std::string&>(animal::str_updateZooKeeper)
                           .build(&Animal::updateZooKeeper),

                rtl::type().member<Animal>()
                           .methodStatic<std::string&&>(animal::str_updateZooKeeper)
                           .build(&Animal::updateZooKeeper)
            #endif
        });

        std::cout << "\n  [t3]\trtl_tests::InitMirror::reflectingAnimal() ==> Done.\n";
    }
}