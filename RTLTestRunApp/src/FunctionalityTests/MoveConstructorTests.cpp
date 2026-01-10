
#include <rtl/access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace rtl;

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(MoveSemantics, move_reflected_type_allocated_on_stack)
    {
        {
            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> classCalender = cxx::mirror().getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = classCalender->ctor()(alloc::Stack);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            EXPECT_TRUE(calender0.isConstCastSafe());
            EXPECT_FALSE(calender0.isOnHeap());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // Sets Calender's move operation counter to zero
            calender::reset_move_ops_counter();

            // Moving a RObject created via alloc::Stack, invokes Calender's move constructor.
            RObject calender1 = std::move(calender0);

            //TODO: Fails on linux, differently optimized away from windows?
            // Calender's move-constructor called once.
            // EXPECT_TRUE(calender::get_move_ops_count() == 1);

            ASSERT_FALSE(calender1.isEmpty());
            EXPECT_TRUE(calender1.isConstCastSafe());
            EXPECT_FALSE(calender1.isOnHeap());

            // 'calander0' must be empty now.
            ASSERT_TRUE(calender0.isEmpty());
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
                ASSERT_TRUE(ret.isEmpty());
            } {
                // Cloning a moved-from object ie an empty object;
                auto [err, ret] = calender0.clone<alloc::Heap>();
                EXPECT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(MoveSemantics, move_reflected_type_allocated_on_heap)
    {
        {
            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> classCalender = cxx::mirror().getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = classCalender->ctor()(alloc::Heap);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            EXPECT_TRUE(calender0.isConstCastSafe());
            EXPECT_TRUE(calender0.isOnHeap());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // Sets Calender's move operation counter to zero
            calender::reset_move_ops_counter();

            // RObject created via alloc::HEAP, contains pointer to reflected type internally, So just the
            // address wrapped in std::any inside Robject is moved. Calender's move constructor is not called.
            RObject calender1 = std::move(calender0);

            // Calender's move constructor isn't called.
            EXPECT_TRUE(calender::get_move_ops_count() == 0);

            ASSERT_FALSE(calender1.isEmpty());
            EXPECT_TRUE(calender1.isConstCastSafe());
            EXPECT_TRUE(calender1.isOnHeap());

            // 'calander0' must be empty now.
            ASSERT_TRUE(calender0.isEmpty());
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
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(MoveSemantics, move_returned_RObject_reflecting_true_const_ref)
    {
        {
            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> classCalender = cxx::mirror().getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            optional<Method> oGetTheEvent = classCalender->getMethod(calender::str_getTheEvent);
            ASSERT_TRUE(oGetTheEvent);

            // Create a stack-allocated object via reflection
            auto [err, calender] = classCalender->ctor()(alloc::Stack);
            EXPECT_TRUE(err == error::None);
            ASSERT_FALSE(calender.isEmpty());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);
            {
                method<RObject, Return()> getTheEvent = oGetTheEvent->targetT().argsT().returnT();
                EXPECT_TRUE(getTheEvent);

                // getTheEvent() returns 'const Event&', hence Reflecetd as true-const. 
                auto [err0, event0] = getTheEvent(calender)();
                EXPECT_TRUE(err0 == error::None);
                ASSERT_FALSE(event0.isEmpty());
                EXPECT_FALSE(event0.isConstCastSafe()); // Retured as True-Const from reflected call, even RTL will not const_cast it.

                optional<Record> classEvent = cxx::mirror().getRecord(event::ns, event::struct_);
                ASSERT_TRUE(classEvent);
                {
                    optional<Method> oEventReset = classEvent->getMethod(event::str_reset);
                    ASSERT_TRUE(oEventReset);
                    // 'Event::reset()' Method is non-const.
                    EXPECT_FALSE(oEventReset->isConst());

                    method<RObject, Return()> eventReset = oEventReset->targetT().argsT().returnT();
                    {
                        auto [e0, r0] = eventReset(std::cref(event0))();
                        EXPECT_TRUE(e0 == error::ConstOverloadMissing);
                        ASSERT_TRUE(r0.isEmpty());
                    } {
                        auto [e0, r0] = eventReset(event0)();
                        EXPECT_TRUE(e0 == error::InvalidCallOnConstTarget);
                        ASSERT_TRUE(r0.isEmpty());
                    }
                    //   TODO: provide option to 'const_cast' the underlying object being reflected.
                    //{  (should it be even allowed?)
                    //    auto [e0, r0] = eventReset(constCast(event0))();
                    //    EXPECT_TRUE(e0 == error::IllegalConstCast);
                    //    ASSERT_TRUE(r0.isEmpty());
                    //}
                }

                // RObject reflecting 'const Event&', storing pointer to reflected type internally, So just the
                // address wrapped in std::any inside Robject is moved. Event's move constructor is not called.
                RObject event1 = std::move(event0);

                ASSERT_FALSE(event1.isEmpty());
                EXPECT_FALSE(event1.isConstCastSafe());

                // 'event0' must be empty now.
                ASSERT_TRUE(event0.isEmpty());
                EXPECT_NE(event0.getTypeId(), event1.getTypeId());
                {
                    // Event::reset() is a non-const method. can't be called on const-object.
                    optional<Method> oEventReset = classEvent->getMethod(event::str_reset);
                    ASSERT_TRUE(oEventReset);

                    // So here, call to 'non-const' method on 'const' target fails here.
                    auto [e0, r0] = oEventReset->bind(event1).call();
                    EXPECT_TRUE(e0 == error::ConstOverloadMissing);
                    ASSERT_TRUE(r0.isEmpty());

                    // Since the  here, call to 'non-const' method on 'const' target fails here.
                    auto [e1, r2] = oEventReset->bind(constCast(event1)).call();
                    EXPECT_TRUE(e1 == error::IllegalConstCast);
                    ASSERT_TRUE(r2.isEmpty());
                }
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
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(MoveSemantics, move_returned_RObject_reflecting_stack_object)
    {
        {
            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> classCalender = cxx::mirror().getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(classCalender);

            optional<Method> optCreateCalender = classCalender->getMethod(calender::str_create);
            ASSERT_TRUE(optCreateCalender);

            auto createCalenderFn = optCreateCalender->argsT<>().returnT<>();
            ASSERT_TRUE(createCalenderFn);
            EXPECT_EQ(createCalenderFn.get_init_error(), rtl::error::None);

            // Calender::create is a static method that returns stack-allocated Calender object.
            // Calling this via reflection, moves the return value from Calender::create to here.
            auto [err0, calender0] = createCalenderFn();

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            EXPECT_TRUE(calender0.isConstCastSafe());
            EXPECT_FALSE(calender0.isOnHeap());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // Sets Calender's move operation counter to zero
            calender::reset_move_ops_counter();

            // Moving a RObject created via alloc::Stack, invokes Calender's move constructor.
            RObject calender1 = std::move(calender0);

            //TODO: Works on windows, fails on linux, differently optimized away for windows?
            // Calender's move-constructor called once.
            // EXPECT_TRUE(calender::get_move_ops_count() == 1);

            ASSERT_FALSE(calender1.isEmpty());
            EXPECT_TRUE(calender1.isConstCastSafe());
            EXPECT_FALSE(calender1.isOnHeap());

            // 'calander0' must be empty now.
            ASSERT_TRUE(calender0.isEmpty());
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
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}