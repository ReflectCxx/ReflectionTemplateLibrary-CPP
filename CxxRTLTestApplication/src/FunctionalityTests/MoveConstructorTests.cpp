
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace rtl;
using namespace test_utils;
using namespace rtl::access;

namespace rtl_tests
{
    TEST(MoveSemantics, move_reflected_type_allocated_on_stack)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> classCalender = cxxMirror.getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = classCalender->create<alloc::Stack>();

            EXPECT_TRUE(err0 == error::None);
            EXPECT_FALSE(calender0.isEmpty());
            EXPECT_FALSE(calender0.isConst());
            EXPECT_FALSE(calender0.isOnHeap());
            EXPECT_FALSE(calender0.isRefOrPtr());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // Moving a RObject created via alloc::Stack, invokes Calender's move constructor.
            RObject calender1 = std::move(calender0);

            EXPECT_FALSE(calender1.isEmpty());
            EXPECT_FALSE(calender1.isConst());
            EXPECT_FALSE(calender1.isOnHeap());
            EXPECT_FALSE(calender1.isRefOrPtr());

            // 'calander0' must be empty now.
            EXPECT_TRUE(calender0.isEmpty());
            EXPECT_NE(calender0.getTypeId(), calender1.getTypeId());

            // After move, these instance count must remain same.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);
            {
                // Cloning a moved-from object ie an empty object;
                auto [err, ret] = calender0.clone<alloc::Stack>();
                EXPECT_TRUE(err == error::EmptyRObject);
                EXPECT_TRUE(ret.isEmpty());
            } {
                // Cloning a moved-from object ie an empty object;
                auto [err, ret] = calender0.clone<alloc::Heap>();
                EXPECT_TRUE(err == error::EmptyRObject);
                EXPECT_TRUE(ret.isEmpty());
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(MoveSemantics, move_reflected_type_allocated_on_heap)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> classCalender = cxxMirror.getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = classCalender->create<alloc::Heap>();

            EXPECT_TRUE(err0 == error::None);
            EXPECT_FALSE(calender0.isEmpty());
            EXPECT_FALSE(calender0.isConst());
            EXPECT_TRUE(calender0.isOnHeap());
            EXPECT_TRUE(calender0.isRefOrPtr());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // RObject created via alloc::HEAP, contains pointer to reflected type internally, So just the
            // address wrapped in std::any inside Robject is moved. Calender's move constructor is not called.
            RObject calender1 = std::move(calender0);

            EXPECT_FALSE(calender1.isEmpty());
            EXPECT_FALSE(calender1.isConst());
            EXPECT_TRUE(calender1.isOnHeap());
            EXPECT_TRUE(calender1.isRefOrPtr());

            // 'calander0' must be empty now.
            EXPECT_TRUE(calender0.isEmpty());
            EXPECT_NE(calender0.getTypeId(), calender1.getTypeId());

            // After move, these instance count must remain same.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(MoveSemantics, move_returned_RObject_reflecting_const_refOrPtr)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> classCalender = cxxMirror.getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            optional<Method> getTheEvent = classCalender->getMethod(calender::str_getTheEvent);
            ASSERT_TRUE(getTheEvent);

            // Create a stack-allocated object via reflection
            auto [err, calender] = classCalender->create<alloc::Stack>();
            EXPECT_TRUE(err == error::None);
            EXPECT_FALSE(calender.isEmpty());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);
            {
                auto [err0, event0] = getTheEvent->bind(calender).call();
                EXPECT_TRUE(err0 == error::None);
                EXPECT_FALSE(event0.isEmpty());
                EXPECT_TRUE(event0.isConst());
                EXPECT_TRUE(event0.isRefOrPtr());

                // RObject reflecting reference/pointer, stores pointer to reflected type internally, So just the
                // address wrapped in std::any inside Robject is moved. Event's move constructor is not called.
                RObject event1 = std::move(event0);

                EXPECT_FALSE(event1.isEmpty());
                EXPECT_TRUE(event1.isConst());
                EXPECT_TRUE(event1.isRefOrPtr());

                // 'event0' must be empty now.
                EXPECT_TRUE(event0.isEmpty());
                EXPECT_NE(event0.getTypeId(), event1.getTypeId());
            }
            // After move, these instance count must remain same.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(MoveSemantics, move_returned_RObject_reflecting_stack_object)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> classCalender = cxxMirror.getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            optional<Method> createCalender = classCalender->getMethod(calender::str_create);
            ASSERT_TRUE(createCalender);

            // Calender::create is a static method that returns stack-allocated Calender object.
            // Calling this via reflection, moves the return value from Calender::create to here.
            auto [err0, calender0] = (*createCalender)()();

            EXPECT_TRUE(err0 == error::None);
            EXPECT_FALSE(calender0.isEmpty());
            EXPECT_FALSE(calender0.isConst());
            EXPECT_FALSE(calender0.isOnHeap());
            EXPECT_FALSE(calender0.isRefOrPtr());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // Moving a RObject created via alloc::Stack, invokes Calender's move constructor.
            RObject calender1 = std::move(calender0);

            EXPECT_FALSE(calender1.isEmpty());
            EXPECT_FALSE(calender1.isConst());
            EXPECT_FALSE(calender1.isOnHeap());
            EXPECT_FALSE(calender1.isRefOrPtr());

            // 'calander0' must be empty now.
            EXPECT_TRUE(calender0.isEmpty());
            EXPECT_NE(calender0.getTypeId(), calender1.getTypeId());

            // After move, these instance count must remain same.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }
}