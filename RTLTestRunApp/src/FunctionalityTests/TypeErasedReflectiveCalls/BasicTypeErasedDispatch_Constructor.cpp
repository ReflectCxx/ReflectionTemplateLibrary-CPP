
#include <rtl/access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"

using namespace test_mirror;

namespace rtl_tests
{
    TEST(TargetTypeErased_rtl_constructor, invalid_erased_return_rtl_constructor)
    {
        {
            rtl::constructor<int> ctor;
            EXPECT_FALSE(ctor);

            auto [err, robj] = ctor(rtl::alloc::Stack, 0);
            EXPECT_EQ(err, rtl::error::InvalidCaller);
            EXPECT_TRUE(robj.isEmpty());
        }
        std::optional<rtl::Record> classStdString = cxx::mirror().getRecord("std", "string"); 
        {
            auto ctor = classStdString->ctor<>();
            EXPECT_TRUE(ctor);

            auto [err, robj] = ctor(rtl::alloc::Stack);
            EXPECT_EQ(err, rtl::error::None);
            EXPECT_FALSE(robj.isEmpty());

            const auto viewStr = robj.view<std::string>();
            ASSERT_TRUE(viewStr);

            const auto& spartaStr = viewStr->get();
            EXPECT_EQ(spartaStr.length(), 0);
        } {
            auto ctor = classStdString->ctor<>();
            EXPECT_TRUE(ctor);

            auto [err, robj] = ctor(rtl::alloc::Heap);
            EXPECT_EQ(err, rtl::error::None);
            EXPECT_FALSE(robj.isEmpty());

            const auto viewStr = robj.view<std::string>();
            ASSERT_TRUE(viewStr);

            const auto& spartaStr = viewStr->get();
            EXPECT_EQ(spartaStr.length(), 0);
        }
        const char* SPARTA = "This is Spaartaaa!!";
        {
            auto ctor = classStdString->ctor<const char*>();
            EXPECT_TRUE(ctor);

            auto [err, robj] = ctor(rtl::alloc::Stack, SPARTA);
            EXPECT_EQ(err, rtl::error::None);
            EXPECT_FALSE(robj.isEmpty());

            const auto viewStr = robj.view<std::string>();
            ASSERT_TRUE(viewStr);

            const auto& spartaStr = viewStr->get();
            EXPECT_EQ(spartaStr, std::string(SPARTA));
        } {
            auto ctor = classStdString->ctor<const char*>();
            EXPECT_TRUE(ctor);

            auto [err, robj] = ctor(rtl::alloc::Heap, SPARTA);
            EXPECT_EQ(err, rtl::error::None);
            EXPECT_FALSE(robj.isEmpty());

            const auto viewStr = robj.view<std::string>();
            ASSERT_TRUE(viewStr);

            const auto& spartaStr = viewStr->get();
            EXPECT_EQ(spartaStr, std::string(SPARTA));
        }
    }
}