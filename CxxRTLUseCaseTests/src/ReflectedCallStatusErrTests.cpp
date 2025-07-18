
/*
* 
* Below error codes are covered in ConstMethodOverloadTests.cpp
* 	error::AmbiguousConstOverload
*	error::ConstMethodOverloadNotFound
*	error::NonConstMethodOverloadNotFound
* and,
*	error::FunctionNotRegisterdInRTL
* is not internally used by RTL.
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
    TEST(ReflectedCallStatusError, error_ConstructorNotRegisteredInRTL)
    {
        optional<Record> classCalender = MyReflection::instance().getRecord(calender::ns, calender::struct_);
        ASSERT_TRUE(classCalender);

        auto [err0, robj0] = classCalender->create<alloc::Stack>();

        ASSERT_TRUE(err0 == error::ConstructorNotRegisteredInRTL);
        ASSERT_TRUE(robj0.isEmpty());

        auto [err1, robj1] = classCalender->create<alloc::Heap>();

        ASSERT_TRUE(err1 == error::ConstructorNotRegisteredInRTL);
        ASSERT_TRUE(robj1.isEmpty());
    }


    TEST(ReflectedCallStatusError, heap__error_CopyConstructorPrivateOrDeleted)
    {
        {
            optional<Record> classDate = MyReflection::instance().getRecord(date::ns, date::struct_);
            ASSERT_TRUE(classDate);

            //Calender's constructor not registered, get its instance from Date's method.
            optional<Method> getCalenderPtr = classDate->getMethod(date::str_getCalenderPtr);
            ASSERT_TRUE(getCalenderPtr);

            // Create Date, which will create a Calander's instance.
            auto [err0, date] = classDate->create<alloc::Stack>();

            // Get the Calander's instance.
            auto [err1, calender] = getCalenderPtr->bind(date).call();
            ASSERT_TRUE(err1 == error::None);
            ASSERT_FALSE(calender.isEmpty());

            ASSERT_TRUE(err1 == error::None);
            ASSERT_FALSE(calender.isEmpty());

            optional<Record> classCalender = MyReflection::instance().getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            // Try to call copy-constructor of class Calender.
            auto [err2, copyObj] = classCalender->clone(calender);

            // Cannot create heap instance: Calender's copy constructor is deleted.
            ASSERT_TRUE(err2 == error::CopyConstructorPrivateOrDeleted);
            ASSERT_TRUE(copyObj.isEmpty());
        }
        EXPECT_TRUE(calender::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ReflectedCallStatusError, construction_on_stack_with_no_copy_ctor___error_CopyConstructorPrivateOrDeleted)
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
            EXPECT_TRUE(calender::assert_zero_instance_count());
            {
                // Attempt to create a reflected instance allocated on the stack.
                auto [err, robj] = classLibrary->create<alloc::Stack>();

            /*  Stack allocation fails:
            *   Creating a stack instance requires storing the actual object inside std::any.
            *   Since std::any requires the contained type T to be copy-constructible for emplacement,
            *   and Library's copy constructor is deleted, construction fails.
            *
            *   Reflection returns error::CopyConstructorPrivateOrDeleted.
            */  ASSERT_TRUE(err == error::CopyConstructorPrivateOrDeleted);
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


    TEST(ReflectedCallStatusError, copy_ctor_on_empty_instance___error_EmptyRObject)
    {
        {
            RObject emptyObj;
            ASSERT_TRUE(emptyObj.isEmpty());

            optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            auto [err, person] = classPerson->clone(emptyObj);

            ASSERT_TRUE(err == error::EmptyRObject);
            ASSERT_TRUE(person.isEmpty());
        }
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
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