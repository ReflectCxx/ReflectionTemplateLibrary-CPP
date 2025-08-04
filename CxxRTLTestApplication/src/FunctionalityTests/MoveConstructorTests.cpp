
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace rtl;
using namespace test_utils;
using namespace rtl::access;

namespace rtl_tests
{
    TEST(ReflectedSmartInstanceTest, robject_copy_construct_on_heap)
    {
        // Ensure a clean start: no previously reflected heap instances alive
        EXPECT_TRUE(date::get_instance_count() == 0);
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
        EXPECT_TRUE(calender::get_instance_count() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Fetch the reflected Record for the 'date' struct
            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            // Create a new instance on the heap
            auto [err0, robj0] = structDate->create<alloc::Heap>();

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(robj0.isEmpty());
            ASSERT_TRUE(robj0.isOnHeap());

            // Only one instance of 'Date' must exists yet.
            EXPECT_TRUE(date::get_instance_count() == 1);
            //'Date' contains a shared_ptr<Calender>.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            {
            /*  Core Concept:
                - This test verifies that copying an RObject pointing to a heap-allocated object
                  results in shared ownership of the same underlying instance.
                - No deep copy or clone of the object is performed.
                - Internally, the shared_ptr ensures reference-counted lifetime.
            */  auto [err3, robj1] = robj0.clone<rtl::alloc::Stack>();
                ASSERT_TRUE(err3 == rtl::error::None);

                // Still only one instance of 'Date' must exists.
                EXPECT_TRUE(date::get_instance_count() == 1);
                // Since only one 'Date' instance exists.
                EXPECT_TRUE(calender::get_instance_count() == 1);

                // Both objects should point to the same heap instance
                ASSERT_FALSE(robj1.isEmpty());
                ASSERT_TRUE(robj1.isOnHeap());
                ASSERT_TRUE(robj0.getTypeId() == robj1.getTypeId());

                // Verify that robj0 and robj1 wrap the same object (by address or semantic equality)
                EXPECT_TRUE(date::test_if_obejcts_are_equal(robj0.get(), robj1.get(), true));

                // Mutate the shared object via robj0
                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                auto [err1, ret] = updateDate->bind(robj0).call(dateStr);
                ASSERT_TRUE(err1 == error::None && ret.isEmpty());

                // The mutation should be visible from both robj0 and robj1
                EXPECT_TRUE(date::test_if_obejcts_are_equal(robj0.get(), robj1.get(), true));

                // Confirm only one reflected heap instance is being tracked
                EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 1);
            }
            // After inner scope ends, one reference should still be alive (robj0)
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 1);
        }
        // All shared_ptrs should be released now - cleanup should be complete
        EXPECT_TRUE(date::get_instance_count() == 0);
        EXPECT_TRUE(calender::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ReflectedSmartInstanceTest, robject_move_construct_on_stack)
    {
        // Ensure there are no reflected stack or heap objects alive before the test begins
        EXPECT_TRUE(date::get_instance_count() == 0);
        EXPECT_TRUE(calender::get_instance_count() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'date' struct
            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            // Create a stack-allocated reflected object
            auto [err0, robj0] = structDate->create<alloc::Stack>();
            ASSERT_TRUE(err0 == error::None);

            // Confirm allocation type and validity
            ASSERT_FALSE(robj0.isEmpty());
            ASSERT_FALSE(robj0.isOnHeap());

            // Only one instance of 'Date' must exists yet.
            EXPECT_TRUE(date::get_instance_count() == 1);
            //'Date' contains a shared_ptr<Calender>.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            {
            /*  RObject move transfers std::any and shared_ptr; robj0 becomes invalid for use.
                robj1 is the sole valid owner after std::move.
            */  RObject robj1 = std::move(robj0);

                // Date's move constructor got called, followed by destructor.
                EXPECT_TRUE(date::get_instance_count() == 1);
                // Calender's move constructor got called, followed by destructor.
                EXPECT_TRUE(calender::get_instance_count() == 1);

                // robj0 got moved to robj1 and invalid now.
                ASSERT_TRUE(robj0.isEmpty());
                // robj1 owns the content & resources.
                ASSERT_FALSE(robj1.isEmpty());
                ASSERT_FALSE(robj1.isOnHeap());
            }
            // Confirm no stack-allocated reflected objects remain after scope ends
            EXPECT_TRUE(date::get_instance_count() == 0);
            EXPECT_TRUE(calender::get_instance_count() == 0);
        }
    }


    TEST(ReflectedSmartInstanceTest, robject_move_construct_on_heap)
    {
        // Ensure clean state before test begins - no lingering reflected heap instances
        EXPECT_TRUE(date::get_instance_count() == 0);
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Fetch the reflected Record representing 'date::struct_'
            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            // Create a new reflected instance on the heap
            auto [err0, robj0] = structDate->create<alloc::Heap>();

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(robj0.isEmpty());
            ASSERT_TRUE(robj0.isOnHeap());

            // Only one instance of 'Date' must exists yet.
            EXPECT_TRUE(date::get_instance_count() == 1);
            //'Date' contains a shared_ptr<Calender>.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            {
            /*  RObject move transfers std::any and shared_ptr; robj0 becomes invalid for use.
                robj1 is the sole valid owner after std::move.
            */  RObject robj1 = std::move(robj0);

                // Date's move constructor didn't get called, just pointer in RObject moved.
                EXPECT_TRUE(date::get_instance_count() == 1);
                // Hence, Calender's move constructor also didn't get called.
                EXPECT_TRUE(calender::get_instance_count() == 1);

                // robj0 got moved to robj1 and invalid now.
                ASSERT_TRUE(robj0.isEmpty());
                // robj1 owns the content & resources.
                ASSERT_FALSE(robj1.isEmpty());
                ASSERT_TRUE(robj1.isOnHeap());

                // Only one heap-allocated reflected instance should be tracked
                ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 1);
            }
            // Since robj1 got destroyed, Date & Calender should too.
            EXPECT_TRUE(date::get_instance_count() == 0);
            EXPECT_TRUE(calender::get_instance_count() == 0);
            // Still within outer scope - heap object still alive and tracked
            ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
        }
    }
}