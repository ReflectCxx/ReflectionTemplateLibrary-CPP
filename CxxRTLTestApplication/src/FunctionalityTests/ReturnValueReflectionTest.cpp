
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsDate.h"
#include "TestUtilsBook.h"
#include "GlobalTestUtils.h"

using namespace test_utils;

namespace rtl_tests 
{
    TEST(ReflecetdReturnValues, verify_typeIds_of_registered_records)
    {
        const auto& rtl_recordIdMap = MyReflection::instance().getRecordIdMap();

        for (const auto& itr0 : MyReflection::instance().getNamespaceRecordMap())
        {
            const auto& namespaceRecordMap = itr0.second;
            for (const auto& itr1 : namespaceRecordMap)
            {
                const std::string& recordName = itr1.first;
                const std::size_t recordId = getRecordIdFor(recordName);
                const auto& itr = rtl_recordIdMap.find(recordId);

                ASSERT_TRUE(itr != rtl_recordIdMap.end());

                const rtl::access::Record& reflectedClass = itr->second.get();

                auto [err, robj] = reflectedClass.create<rtl::alloc::Stack>();

                if (recordName == calender::struct_) {
                    //Calender's constructor not registered in RTL.
                    EXPECT_TRUE(err == rtl::error::ConstructorNotRegisteredInRTL);
                    EXPECT_TRUE(robj.isEmpty());
                }
                else if (recordName == library::class_) {
                    //Library's copy-constructor is deleted or private.
                    EXPECT_TRUE(err == rtl::error::CopyConstructorPrivateOrDeleted);
                    EXPECT_TRUE(robj.isEmpty());
                }
                else {

                    EXPECT_TRUE(err == rtl::error::None);
                    EXPECT_FALSE(robj.isEmpty());
                    EXPECT_TRUE(robj.getTypeId() == recordId);
                }
            }
        }
    }


    TEST(ReflecetdReturnValues, on_registered_return_type__test_disabled_ctors)
    {        
        auto structCalender = MyReflection::instance().getRecord(id::calender);
        ASSERT_TRUE(structCalender);

        auto [err, robj] = structCalender->create<rtl::alloc::Stack>();

        //Calender's constructor not registered in RTL.
        EXPECT_TRUE(err == rtl::error::ConstructorNotRegisteredInRTL);
        EXPECT_TRUE(robj.isEmpty());
        {
            auto structDate = MyReflection::instance().getRecord(id::date);
            ASSERT_TRUE(structDate);

            auto [err0, date] = structDate->create<rtl::alloc::Stack>();

            EXPECT_TRUE(err0 == rtl::error::None);
            EXPECT_FALSE(date.isEmpty());

            //'Date' has-a 'Calender', so creates its instance.
            EXPECT_TRUE(calender::get_instance_count() == 1);

            auto getCalender = structDate->getMethod(date::str_getCalenderRef);
            ASSERT_TRUE(getCalender);

            auto [err1, calender] = getCalender->bind(date).call();
            EXPECT_TRUE(err1 == rtl::error::None);
            EXPECT_FALSE(calender.isEmpty());
            EXPECT_TRUE(calender.getTypeId() == id::calender);

            //clone always creates instance on heap.
            auto [err2, robj2] = calender.clone<rtl::alloc::Heap>();
            //Calender's copy-constructor private or deleted.
            EXPECT_TRUE(err2 == rtl::error::CopyConstructorPrivateOrDeleted);
            {
            /*  Copy-constructs on stack successfully.
                No actual deep copy occurs, RObject internally holds a const pointer/reference to the original instance.
                The underlying object's copy constructor is not invoked; only the RObject wrapper is copied.
            */  auto [err3, cal] = calender.clone<rtl::alloc::Stack>();

                ASSERT_TRUE(err3 == rtl::error::None);
                ASSERT_FALSE(cal.isEmpty());
                ASSERT_TRUE(cal.getTypeId() == id::calender);
                EXPECT_TRUE(calender::get_instance_count() == 1);
            }
        }
        //Once 'Date' is destryoyed, 'Calender' should too.
        ASSERT_TRUE(calender::assert_zero_instance_count());
    }


    TEST(ReflecetdReturnValues, on_registered_return_type__test_ctors_dctor_copies)
    {
        auto structCalender = MyReflection::instance().getRecord(id::calender);
        ASSERT_TRUE(structCalender);

        auto getInstance = structCalender->getMethod(calender::str_create);
        ASSERT_TRUE(getInstance);
        {
            auto [err, calender] = getInstance->bind().call();

            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(calender.isEmpty());
            EXPECT_TRUE(calender.getTypeId() == id::calender);
        }

        ASSERT_TRUE(calender::assert_zero_instance_count());
    }
}