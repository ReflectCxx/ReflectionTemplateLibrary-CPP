
/*
* 
* Below error codes are covered in ConstMethodOverloadTests.cpp
*   rtl::error::IllegalConstCast
* 	rtl::error::AmbiguousConstOverload
*	rtl::error::ConstOverloadMissing
*	rtl::error::NonConstOverloadMissing
*   rtl::error::ConstCallViolation
* 
* Covered in ReturnTypeErasedDispatch.cpp
*   rtl::error::ExplicitRefBindingRequired
* 
* and,
*	rtl::error::FunctionNotRegistered, is not internally used by RTL.
* Function/Method objects are returned wrapped in std::optional<>, which will 
* be empty if its not in registered in Reflection-system.
* 
*/


#include <rtl/rtl_access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl;

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(ReflectionOperationStatus, error_EmptyRObject)
    {
        {
            RObject emptyObj;
            ASSERT_TRUE(emptyObj.isEmpty());
            {
                auto [err, person] = emptyObj.clone<alloc::Stack>();
                EXPECT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(person.isEmpty());
            } {
                auto [err, person] = emptyObj.clone<alloc::Heap>();
                EXPECT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(person.isEmpty());
            }
        }
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ReflectionOperationStatus, error_TypeNotDefaultConstructible)
    {
        optional<Record> classEvent = cxx::mirror().getRecord(event::ns, event::struct_);
        ASSERT_TRUE(classEvent);

        auto [err0, robj0] = classEvent->ctor()(alloc::Stack);

        EXPECT_TRUE(err0 == error::TypeNotDefaultConstructible);
        ASSERT_TRUE(robj0.isEmpty());

        auto [err1, robj1] = classEvent->ctor()(alloc::Heap);

        EXPECT_TRUE(err1 == error::TypeNotDefaultConstructible);
        ASSERT_TRUE(robj1.isEmpty());
    }


    TEST(ReflectionOperationStatus, error_ReflectedObjectIsNotInWrapper)
    {
        char ch = 'R';
        RObject rCh = rtl::reflect(ch);
        EXPECT_FALSE(rCh.isAllocatedByRtl());
        {
            auto [err, rch] = rCh.clone<alloc::Stack, copy::Value>();
            EXPECT_TRUE(err == error::None);
            ASSERT_FALSE(rch.isEmpty());
            EXPECT_TRUE(rch.canViewAs<char>());
            EXPECT_EQ(rch.view<char>()->get(), 'R');
        } 
        EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
        {
            auto [err, rch] = rCh.clone<alloc::Heap, copy::Value>();
            EXPECT_TRUE(err == error::None);
            ASSERT_FALSE(rch.isEmpty());
            EXPECT_TRUE(rch.canViewAs<char>());
            EXPECT_EQ(rch.view<char>()->get(), 'R');
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
        {
            auto [err, rch] = rCh.clone<alloc::Stack, copy::Wrapper>();
            EXPECT_TRUE(err == error::NotWrapperType);
            ASSERT_TRUE(rch.isEmpty());
        /*  this will not compile, fail with message -
            static_assert failed: 'Heap allocation forbidden for STL-Wrappers (e.g. smart pointers/optionals/reference_wrappers).' */
        //  auto [err0, rch0] = rChptr.clone<alloc::Heap, entityKind::Wrapper>();
        }
    }


    TEST(ReflectionOperationStatus, std_unique_ptr__error_TypeNotCopyConstructible)
    {
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
        std::unique_ptr<char> chPtr = std::make_unique<char>('R');

        {
            RObject rChptr = rtl::reflect(chPtr);
            
            ASSERT_FALSE(rChptr.isEmpty());
            EXPECT_FALSE(rChptr.isAllocatedByRtl());
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);

            //error reterr = cxx::mirror().setupCloning(rChptr);
            //ASSERT_TRUE(reterr == error::None);

            EXPECT_TRUE(rChptr.canViewAs<char>());
            {
                auto viewCh = rChptr.view<char>();
                ASSERT_TRUE(viewCh);

                char ch = viewCh->get();
                EXPECT_EQ(ch, 'R');
            } {
                //Try to create copy of std::unique_ptr on stack.
                auto [err, rch0] = rChptr.clone<alloc::Stack>();
                EXPECT_TRUE(err == error::TypeNotCopyConstructible);
            } {
                // Try to create copy of std::unique_ptr explicitly on stack.
                auto [err, rch0] = rChptr.clone<alloc::Stack, copy::Wrapper>();
                EXPECT_TRUE(err == error::TypeNotCopyConstructible);
            } {
                // Try to create copy of std::unique_ptr on heap.
                auto [err, rch0] = rChptr.clone<alloc::Heap>();
                EXPECT_TRUE(err == error::StlWrapperHeapAllocForbidden);
            } {
                // Now try to create copy of std::unique_ptr explicitly on heap.
                auto [err, rch0] = rChptr.clone<alloc::Heap, copy::Wrapper>();
                EXPECT_TRUE(err == error::StlWrapperHeapAllocForbidden);
            } {
                // but we can definitly create the copy of underlying value.
                auto [err, rch0] = rChptr.clone<alloc::Stack, copy::Value>();
                EXPECT_TRUE(err == error::None);
                ASSERT_FALSE(rch0.isEmpty());
                EXPECT_TRUE(rch0.canViewAs<char>());

                auto viewCh = rChptr.view<char>();
                ASSERT_TRUE(viewCh);

                char ch = viewCh->get();
                EXPECT_EQ(ch, 'R');
            }
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
            {
                // but we can definitly create the copy of underlying value.
                auto [err, rch0] = rChptr.clone<alloc::Heap, copy::Value>();
                EXPECT_TRUE(err == error::None);
                ASSERT_FALSE(rch0.isEmpty());
                ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 2);
                EXPECT_TRUE(rch0.canViewAs<char>());

                auto viewCh = rChptr.view<char>();
                ASSERT_TRUE(viewCh);

                char ch = viewCh->get();
                EXPECT_EQ(ch, 'R');
            }
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
        }
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ReflectionOperationStatus, copy_construct__error_TypeNotCopyConstructible)
    {
        {
            optional<Record> classCalender = cxx::mirror().getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            //Events's constructor not registered, get its instance from 'Calander'.
            optional<Method> getEvent = classCalender->getMethod(calender::str_getTheEvent);
            ASSERT_TRUE(getEvent);

            // Create Calender, which will create a Event's instance.
            auto [err0, calender] = classCalender->ctor()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender.isEmpty());

            auto get_event = getEvent->targetT<>().argsT<>().returnT<>();

            // Get the Event's instance.
            auto [err1, event] = get_event(calender)();
            EXPECT_TRUE(err1 == error::None);
            ASSERT_FALSE(event.isEmpty());

            // Try to call copy-constructor of class Event.
            auto [err3, eventCp1] = event.clone<alloc::Heap>();

            // Cannot create heap instance: Calender's copy constructor is deleted.
            EXPECT_TRUE(err3 == error::TypeNotCopyConstructible);
            ASSERT_TRUE(eventCp1.isEmpty());
        }
        EXPECT_TRUE(calender::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ReflectionOperationStatus, alloc_on_stack__error_TypeNotCopyConstructible)
    {
        {
            // Fetch the reflected Record for class 'Library'.
            optional<Record> classLibrary = cxx::mirror().getRecord(library::class_);
            ASSERT_TRUE(classLibrary);
            {
                // Attempt to create a reflected instance allocated on the heap.
                auto [err, robj] = classLibrary->ctor()(alloc::Heap);
            /*  Heap allocation succeeds:
            *   Even though Library's copy constructor is deleted, RObject internally stores
            *   the pointer directly inside std::any (type-erased), without requiring the type T
            *   to be copy-constructible.
            */  EXPECT_TRUE(err == error::None);
                ASSERT_FALSE(robj.isEmpty());
            }
            // Ensure no leaked or lingering reflected instances.
            EXPECT_TRUE(library::assert_zero_instance_count());
            {
                // Attempt to create a reflected instance allocated on the stack.
                auto [err, robj] = classLibrary->ctor()(alloc::Stack);
            /*  Stack allocation fails:
            *   Creating a stack instance requires storing the actual object inside std::any.
            *   Since std::any requires the contained type T to be copy-constructible for emplacement,
            *   and Library's copy constructor is deleted, construction fails.
            */  EXPECT_TRUE(err == error::TypeNotCopyConstructible);
                ASSERT_TRUE(robj.isEmpty());
            }
        }
    }


    TEST(ReflectionOperationStatus, static_method_call__error_SignatureMismatch)
    {
        optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
        ASSERT_TRUE(classPerson);

        optional<Method> optGetProfile = classPerson->getMethod(person::str_getProfile);
        ASSERT_TRUE(optGetProfile);
        EXPECT_TRUE(optGetProfile->hasSignature<>());  //empty template params checks for zero arguments.

        rtl::static_method<rtl::Return(std::string)> getProfileFn = optGetProfile->argsT<std::string>().returnT<>();
        EXPECT_FALSE(getProfileFn);
        EXPECT_EQ(getProfileFn.get_init_error(), error::SignatureMismatch);

        auto [err, robj] = getProfileFn(std::string());
        EXPECT_EQ(err, error::SignatureMismatch);
        EXPECT_TRUE(robj.isEmpty());
    }


    TEST(ReflectionOperationStatus, method_call__error_EmptyRObject)
    {
        {
            RObject emptyObj;
            ASSERT_TRUE(emptyObj.isEmpty());

            optional<Record> classBook = cxx::mirror().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err, ret] = classBook->getMethod(book::str_getPublishedOn)
                                       ->targetT().argsT().returnT()(emptyObj)();

            EXPECT_TRUE(err == error::EmptyRObject);
            ASSERT_TRUE(ret.isEmpty());
        }
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ReflectionOperationStatus, method_call_using_heap_object__error_TargetMismatch)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Record> classBook = cxx::mirror().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, person] = classPerson->ctor()(alloc::Heap);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());

            optional<Method> oGetPublishedOn = classBook->getMethod(book::str_getPublishedOn);
            ASSERT_TRUE(oGetPublishedOn);
            
            rtl::method<rtl::RObject, rtl::Return()> getPublishedOn = oGetPublishedOn->targetT().argsT().returnT();
            EXPECT_TRUE(getPublishedOn);

            auto [err1, ret] = getPublishedOn(person)();
            EXPECT_TRUE(err1 == error::TargetTypeMismatch);
            ASSERT_TRUE(ret.isEmpty());
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ReflectionOperationStatus, method_call_using_stack_object__error_TargetMismatch)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Record> classBook = cxx::mirror().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, person] = classPerson->ctor()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());

            optional<Method> oGetPublishedOn = classBook->getMethod(book::str_getPublishedOn);
            ASSERT_TRUE(oGetPublishedOn);

            rtl::method<rtl::RObject, rtl::Return()> getPublishedOn = oGetPublishedOn->targetT().argsT().returnT();
            EXPECT_TRUE(getPublishedOn);

            auto [err1, ret] = getPublishedOn(person)();
            EXPECT_TRUE(err1 == error::TargetTypeMismatch);
            ASSERT_TRUE(ret.isEmpty());
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}