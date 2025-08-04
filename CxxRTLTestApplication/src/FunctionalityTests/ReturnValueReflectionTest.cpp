
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsDate.h"
#include "TestUtilsBook.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace rtl_tests 
{
    TEST(ReflecetdReturnValues, on_registered_return_type__test_cloning)
    {   
        //I don't know if the 'Event' is class or struct..Reflection YaY!. :P
        auto classEvent = MyReflection::instance().getRecord(id::event);
        ASSERT_TRUE(classEvent);

        auto [err0, robj0] = classEvent->create<rtl::alloc::Stack>();

        //Event's constructor not registered in RTL.
        EXPECT_TRUE(err0 == rtl::error::ConstructorNotRegisteredInRtl);
        EXPECT_TRUE(robj0.isEmpty());
        {
            auto classCalender = MyReflection::instance().getRecord(id::calender);
            ASSERT_TRUE(classCalender);

            auto [err1, calender] = classCalender->create<rtl::alloc::Stack>();

            EXPECT_TRUE(err1 == rtl::error::None);
            EXPECT_FALSE(calender.isEmpty());

            // 'Calender' instance created.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has two 'Event' instances.
            EXPECT_TRUE(event::get_instance_count() == 2);

            auto getEvent = classCalender->getMethod(calender::str_getTheEvent);
            ASSERT_TRUE(getEvent);

            auto [err2, event] = getEvent->bind(calender).call();
            EXPECT_TRUE(err2 == rtl::error::None);
            EXPECT_FALSE(event.isEmpty());
            //'getEvent' returns 'const Event&'
            EXPECT_TRUE(event.isRefOrPtr());
            EXPECT_TRUE(event.getTypeId() == id::event);
            {
                auto [err, robj] = event.clone<rtl::alloc::Heap>();
                //Event's copy-constructor private or deleted.
                EXPECT_TRUE(err == rtl::error::Instantiating_typeNotCopyConstructible);
                EXPECT_TRUE(robj.isEmpty());
                // Two 'Event' instances, owned by 'Calender'
                EXPECT_TRUE(event::get_instance_count() == 2);
            } {
                auto [err, robj] = event.clone<rtl::alloc::Stack>();
                //'event' contains refrence of 'Event', no Copy-ctor is called.
                EXPECT_TRUE(err == rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());
                // Two 'Event' instances, owned by 'Calender'
                EXPECT_TRUE(event::get_instance_count() == 2);
            }
        }
        ASSERT_TRUE(calender::assert_zero_instance_count());
        //Once 'Calender' is destryoyed, all 'Event's should too.
        ASSERT_TRUE(event::assert_zero_instance_count());
    }


    //TEST(ReflecetdReturnValues, on_registered_return_type__test_ctors_dctor_copies)
    //{
    //    auto structCalender = MyReflection::instance().getRecord(id::calender);
    //    ASSERT_TRUE(structCalender);

    //    auto getInstance = structCalender->getMethod(calender::str_create);
    //    ASSERT_TRUE(getInstance);
    //    {
    //        auto [err, calender] = getInstance->bind().call();

    //        EXPECT_TRUE(err == rtl::error::None);
    //        ASSERT_FALSE(calender.isEmpty());
    //        EXPECT_TRUE(calender.getTypeId() == id::calender);
    //    }

    //    ASSERT_TRUE(calender::assert_zero_instance_count());
    //}
}