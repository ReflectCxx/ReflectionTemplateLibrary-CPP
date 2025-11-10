
#include <rtl/access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsDate.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(ReflecetdReturnValues, on_registered_return_type__test_cloning)
    {   
        //I don't know if the 'Event' is class or struct..Reflection YaY!. :P
        auto classEvent = cxx::mirror().getRecord(cxx::reflected_id(event::struct_));
        ASSERT_TRUE(classEvent);

        auto [err0, robj0] = classEvent->create<rtl::alloc::Stack>();

        //Event's constructor is private, not accessible, Hence the error.
        EXPECT_TRUE(err0 == rtl::error::TypeNotDefaultConstructible);
        ASSERT_TRUE(robj0.isEmpty());
        {
            auto classCalender = cxx::mirror().getRecord(cxx::reflected_id(calender::struct_));
            ASSERT_TRUE(classCalender);

            auto [err1, calender] = classCalender->create<rtl::alloc::Stack>();

            EXPECT_TRUE(err1 == rtl::error::None);
            ASSERT_FALSE(calender.isEmpty());

            // 'Calender' instance created.
            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has two 'Event' instances.
            EXPECT_TRUE(event::get_instance_count() == 2);

            // Event's object can be obtained from Calender's object ('Calander' has-a 'Event').
            auto getEvent = classCalender->getMethod(calender::str_getTheEvent);
            ASSERT_TRUE(getEvent);

            // get the Event's object from the 'Calender' object.
            auto [err2, event] = getEvent->bind(calender).call();
            EXPECT_TRUE(err2 == rtl::error::None);
            ASSERT_FALSE(event.isEmpty());
            EXPECT_TRUE(event.getTypeId() == cxx::reflected_id(event::struct_));
            {
                {
                    auto [err, robj] = event.clone<rtl::alloc::Heap>();
                    EXPECT_TRUE(err == rtl::error::CloningDisabled);
                }
                
                rtl::error reterr = cxx::mirror().setupCloning(event);
                ASSERT_TRUE(reterr == rtl::error::None);
                
                {
                    auto [err, robj] = event.clone<rtl::alloc::Heap>();
                    //Event's copy-constructor private or deleted.
                    EXPECT_TRUE(err == rtl::error::TypeNotCopyConstructible);
                    ASSERT_TRUE(robj.isEmpty());
                    // Two 'Event' instances, owned by 'Calender'
                    EXPECT_TRUE(event::get_instance_count() == 2);
                }
            } {
                auto [err, robj] = event.clone<rtl::alloc::Stack>();
                //Event's copy-constructor private or deleted.
                EXPECT_TRUE(err == rtl::error::TypeNotCopyConstructible);
                ASSERT_TRUE(robj.isEmpty());
                // Still, two 'Event' instances, owned by 'Calender'
                EXPECT_TRUE(event::get_instance_count() == 2);
            }
        }
        EXPECT_TRUE(calender::assert_zero_instance_count());
        //Once 'Calender' is destroyed, all 'Event's should too.
        ASSERT_TRUE(event::assert_zero_instance_count());
    }
}