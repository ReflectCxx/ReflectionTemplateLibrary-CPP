
/*
* 
* Below error codes are covered in ConstMethodOverloadTests.cpp
* 	rtl::error::AmbiguousConstOverload
*	rtl::error::ConstMethodOverloadNotFound
*	rtl::error::NonConstMethodOverloadNotFound
*   rtl::error::ImplicitCallToNonConstOnConstTarget
* and,
*	rtl::error::FunctionNotRegisterdInRTL, is not internally used by RTL.
* Function/Method objects are returned wrapped in std::optional<>, which will 
* be empty if its not in registered in Reflection-system.
* 
*/

#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests
{
    TEST(ReflectedCallStatusError, clone_empty_instance___error_EmptyRObject)
    {
        {
            RObject emptyObj;
            ASSERT_TRUE(emptyObj.isEmpty());
            {
                auto [err, person] = emptyObj.clone<alloc::Stack>();
                ASSERT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(person.isEmpty());
            } {
                auto [err, person] = emptyObj.clone<alloc::Heap>();
                ASSERT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(person.isEmpty());
            }
        }
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ReflectedCallStatusError, error_ConstructorNotRegisteredInRTL)
    {
        optional<Record> classEvent = MyReflection::instance().getRecord(event::ns, event::struct_);
        ASSERT_TRUE(classEvent);

        auto [err0, robj0] = classEvent->create<alloc::Stack>();

        ASSERT_TRUE(err0 == error::ConstructorNotRegisteredInRtl);
        ASSERT_TRUE(robj0.isEmpty());

        auto [err1, robj1] = classEvent->create<alloc::Heap>();

        ASSERT_TRUE(err1 == error::ConstructorNotRegisteredInRtl);
        ASSERT_TRUE(robj1.isEmpty());
    }


    TEST(ReflectedCallStatusError, error_Instantiating_typeNotCopyConstructible)
    {
        {
            optional<Record> classCalender = MyReflection::instance().getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            //Events's constructor not registered, get its instance from 'Calander'.
            optional<Method> getEvent = classCalender->getMethod(calender::str_getTheEvent);
            ASSERT_TRUE(getEvent);

            // Create Calender, which will create a Event's instance.
            auto [err0, calender] = classCalender->create<alloc::Stack>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender.isEmpty());

            // Get the Event's instance.
            auto [err1, event] = getEvent->bind(calender).call();
            ASSERT_TRUE(err1 == error::None);
            ASSERT_FALSE(event.isEmpty());

            // Try to call copy-constructor of class Event.
            auto [err2, eventCp] = event.clone<alloc::Heap>();

            // Cannot create heap instance: Calender's copy constructor is deleted.
            ASSERT_TRUE(err2 == error::Instantiating_typeNotCopyConstructible);
            ASSERT_TRUE(eventCp.isEmpty());
        }
        EXPECT_TRUE(calender::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ReflectedCallStatusError, on_construction___error_Instantiating_typeNotCopyConstructible)
    {
        {
            // Fetch the reflected Record for class 'Library'.
            optional<Record> classLibrary = MyReflection::instance().getRecord(library::class_);
            ASSERT_TRUE(classLibrary);
            {
                // Attempt to create a reflected instance allocated on the heap.
                auto [err, robj] = classLibrary->create<alloc::Heap>();

            /*
            *   Heap allocation succeeds:
            *   Even though Library's copy constructor is deleted, RObject internally stores
            *   the pointer directly inside std::any (type-erased), without requiring the type T
            *   to be copy-constructible.
            */  ASSERT_TRUE(err == error::None);
                ASSERT_FALSE(robj.isEmpty());
            }
            // Ensure no leaked or lingering reflected instances.
            EXPECT_TRUE(library::assert_zero_instance_count());
            {
                // Attempt to create a reflected instance allocated on the stack.
                auto [err, robj] = classLibrary->create<alloc::Stack>();

            /*  Stack allocation fails:
            *   Creating a stack instance requires storing the actual object inside std::any.
            *   Since std::any requires the contained type T to be copy-constructible for emplacement,
            *   and Library's copy constructor is deleted, construction fails.
            */  ASSERT_TRUE(err == error::Instantiating_typeNotCopyConstructible);
                ASSERT_TRUE(robj.isEmpty());
            }
        }
    }


    TEST(ReflectedCallStatusError, static_method_call_wrong_args___error_SignatureMismatch)
    {
        optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
        ASSERT_TRUE(classPerson);

        optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
        ASSERT_TRUE(getProfile);
        ASSERT_TRUE(getProfile->hasSignature<>());  //empty template params checks for zero arguments.

        auto [err, robj] = getProfile->bind().call(std::string());

        ASSERT_TRUE(err == error::SignatureMismatch);
        ASSERT_TRUE(robj.isEmpty());
    }


    TEST(ReflectedCallStatusError, method_call_on_empty_instance___error_EmptyRObject)
    {
        {
            RObject emptyObj;
            ASSERT_TRUE(emptyObj.isEmpty());

            optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err, ret] = classBook->getMethod(book::str_getPublishedOn)->bind(emptyObj).call();
            ASSERT_TRUE(err == error::EmptyRObject);
            ASSERT_TRUE(ret.isEmpty());
        }
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ReflectedCallStatusError, method_on_wrong_heap_instance___error_MethodTargetMismatch)
    {
        {
            optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, person] = classPerson->create<alloc::Heap>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());

            optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
            ASSERT_TRUE(getPublishedOn);

            auto [err1, ret] = getPublishedOn->bind(person).call();
            ASSERT_TRUE(err1 == error::MethodTargetMismatch);
            ASSERT_TRUE(ret.isEmpty());
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ReflectedCallStatusError, method_on_wrong_stack_instance___error_MethodTargetMismatch)
    {
        {
            optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, person] = classPerson->create<alloc::Stack>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());

            optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
            ASSERT_TRUE(getPublishedOn);

            auto [err1, ret] = getPublishedOn->bind(person).call();
            ASSERT_TRUE(err1 == error::MethodTargetMismatch);
            ASSERT_TRUE(ret.isEmpty());
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }
}