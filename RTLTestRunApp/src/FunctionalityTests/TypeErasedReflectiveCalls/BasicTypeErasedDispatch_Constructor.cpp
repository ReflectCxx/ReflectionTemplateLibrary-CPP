
#include <rtl/access.h>
#include <gtest/gtest.h>

#include "GlobalTestUtils.h"
#include "TestMirrorProvider.h"
#include "../CxxTestProps/inc/StringWrap.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(TargetTypeErased_rtl_constructor, std_string_constructor_call)
    {
        {
            rtl::constructor<int> ctor;
            EXPECT_FALSE(ctor);

            auto [err, robj] = ctor(rtl::alloc::Stack, 0);
            EXPECT_EQ(err, rtl::error::InvalidCaller);
            EXPECT_TRUE(robj.isEmpty());
        }
        std::optional<rtl::Record> classStdString = cxx::mirror().getRecord("std", "string");
        ASSERT_TRUE(classStdString);
        {
            auto createAndTestOn = [&](rtl::alloc alloc_on)
            {
                auto ctor = classStdString->ctor<>();
                EXPECT_TRUE(ctor);

                auto [err, robj] = ctor(alloc_on);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<std::string>();
                ASSERT_TRUE(viewStr);

                const auto& spartaStr = viewStr->get();
                EXPECT_EQ(spartaStr.length(), 0);
            };
            createAndTestOn(rtl::alloc::Heap);
            createAndTestOn(rtl::alloc::Stack);
        } 
        const char* SPARTA = "This is Spaartaaa!!";
        {
            auto createAndTestOn = [&](rtl::alloc alloc_on)
            {
                auto ctor = classStdString->ctor<const char*>();
                EXPECT_TRUE(ctor);

                auto [err, robj] = ctor(alloc_on, SPARTA);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<std::string>();
                ASSERT_TRUE(viewStr);

                const auto& spartaStr = viewStr->get();
                EXPECT_EQ(spartaStr, std::string(SPARTA));
            };
            createAndTestOn(rtl::alloc::Heap);
            createAndTestOn(rtl::alloc::Stack);
        }
    }


    TEST(TargetTypeErased_rtl_constructor, typed_constructor_call)
    {
        std::optional<rtl::Record> classStrWrap = cxx::mirror().getRecord(StrWrap::struct_);
        ASSERT_TRUE(classStrWrap);
        {
            auto createAndTestOn = [&](rtl::alloc alloc_on)
            {
                auto ctor = classStrWrap->ctor<>();
                EXPECT_TRUE(ctor);

                auto [err, robj] = ctor(alloc_on);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrap>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(), (std::string(DEFAULT_str) + SUFFIX_ctor));
            };
            createAndTestOn(rtl::alloc::Heap);
            createAndTestOn(rtl::alloc::Stack);
        }
        const char* SPARTA = "This is Spaartaaa!!";
        {
            auto createAndTestOn = [&](rtl::alloc alloc_on)
            {
                auto ctor = classStrWrap->ctor<std::string_view>();
                EXPECT_TRUE(ctor);

                auto [err, robj] = ctor(alloc_on, SPARTA);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrap>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(), (std::string(SPARTA) + SUFFIX_std_string_view + SUFFIX_ctor));
            };
            createAndTestOn(rtl::alloc::Heap);
            createAndTestOn(rtl::alloc::Stack);
        } {
            auto createAndTestOn = [&](rtl::alloc alloc_on)
            {
                auto ctor = classStrWrap->ctor<const char*>();
                EXPECT_TRUE(ctor);

                auto [err, robj] = ctor(alloc_on, SPARTA);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrap>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(), (std::string(SPARTA) + SUFFIX_const_char_ptr + SUFFIX_ctor));
            };
            createAndTestOn(rtl::alloc::Heap);
            createAndTestOn(rtl::alloc::Stack);
        }
    }
}