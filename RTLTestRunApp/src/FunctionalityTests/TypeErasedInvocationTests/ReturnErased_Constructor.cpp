
#include <rtl_access.h>
#include <gtest/gtest.h>

#include "GlobalTestUtils.h"
#include "TestMirrorProvider.h"
#include "../CxxTestProps/inc/StringWrap.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(ReturnErased_Constructor, std_string_constructor_call)
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
            auto testCreateOn = [&](rtl::alloc alloc_on)
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
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        } 
        const char* SPARTA = "This is Spaartaaa!!";
        {
            auto testCreateOn = [&](rtl::alloc alloc_on)
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
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        }
    }


    TEST(ReturnErased_Constructor, by_value_overloaded_ctor_call)
    {
        std::optional<rtl::Record> classStrWrap = cxx::mirror().getRecord(StrWrapA::struct_);
        ASSERT_TRUE(classStrWrap);
        {
            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto ctor = classStrWrap->ctor<>();
                EXPECT_TRUE(ctor);

                auto [err, robj] = ctor(alloc_on);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrapA>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(), 
                    (std::string(StrWrapA::struct_) + SUFFIX_ctor));
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        }
        const char* SPARTA = "This is Spaartaaa!!";
        {
            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto ctor = classStrWrap->ctor<std::string_view>();
                EXPECT_TRUE(ctor);

                auto [err, robj] = ctor(alloc_on, SPARTA);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrapA>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(), 
                    (std::string(StrWrapA::struct_) + std::string(SPARTA) + 
                        SUFFIX_std_string_view + SUFFIX_ctor));
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        } {
            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto ctor = classStrWrap->ctor<const char*>();
                EXPECT_TRUE(ctor);

                auto [err, robj] = ctor(alloc_on, SPARTA);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrapA>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(),
                    (std::string(StrWrapA::struct_) + std::string(SPARTA) + 
                        SUFFIX_const_char_ptr + SUFFIX_ctor));
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        }
    }


    TEST(ReturnErased_Constructor, by_ref_overloaded_ctor_call)
    {
        const char* SPARTA = "This is Spaartaaa!!";
        std::optional<rtl::Record> classStrWrap = cxx::mirror().getRecord(StrWrapA::struct_);
        ASSERT_TRUE(classStrWrap);

        auto ctor = classStrWrap->ctor<std::string>();
        EXPECT_TRUE(ctor);
        {
            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto [err, robj] = ctor.bind<std::string&>()(alloc_on, SPARTA);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrapA>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(),
                    (std::string(StrWrapA::struct_) + std::string(SPARTA) + 
                        SUFFIX_std_string_lvref + SUFFIX_ctor));
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        } {
            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto [err, robj] = ctor.bind<std::string&&>()(alloc_on, SPARTA);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrapA>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(),
                    (std::string(StrWrapA::struct_) + std::string(SPARTA) + 
                        SUFFIX_std_string_rvref + SUFFIX_ctor));
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        } {
            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto [err, robj] = ctor.bind<const std::string&>()(alloc_on, SPARTA);
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrapA>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(),
                    (std::string(StrWrapA::struct_) + std::string(SPARTA) + 
                        SUFFIX_std_string_clvref + SUFFIX_ctor));
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        }
    }

    
    TEST(ReturnErased_Constructor, auto_overload_resolution)
    {
        const char* SPARTA = "This is Spaartaaa!!";
        {
            std::optional<rtl::Record> classStrWrap = cxx::mirror().getRecord(StrWrapA::struct_);
            ASSERT_TRUE(classStrWrap);

            auto ctor = classStrWrap->ctor<std::string>();
            EXPECT_TRUE(ctor);

            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto [err, robj] = ctor(alloc_on, SPARTA);
                // More than one reference-based overloads exists.
                EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
                EXPECT_TRUE(robj.isEmpty());
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        } {
            std::optional<rtl::Record> classStrWrap = cxx::mirror().getRecord(StrWrapB::struct_);
            ASSERT_TRUE(classStrWrap);

            auto ctor = classStrWrap->ctor<std::string>();
            EXPECT_TRUE(ctor);

            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto [err, robj] = ctor(alloc_on, SPARTA);
                // More than one reference-based overloads exists.
                EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
                EXPECT_TRUE(robj.isEmpty());
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        } {
            std::optional<rtl::Record> classStrWrap = cxx::mirror().getRecord(StrWrapC::struct_);
            ASSERT_TRUE(classStrWrap);

            auto ctor = classStrWrap->ctor<std::string>();
            EXPECT_TRUE(ctor);

            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto [err, robj] = ctor(alloc_on, SPARTA);
                // only non-const-reference-based ctor exists.
                // mutating call should be explicit.
                EXPECT_EQ(err, rtl::error::ExplicitRefBindingRequired);
                EXPECT_TRUE(robj.isEmpty());
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        } {
            std::optional<rtl::Record> classStrWrap = cxx::mirror().getRecord(StrWrapD::struct_);
            ASSERT_TRUE(classStrWrap);

            auto ctor = classStrWrap->ctor<std::string>();
            EXPECT_TRUE(ctor);

            auto testCreateOn = [&](rtl::alloc alloc_on)
            {
                auto [err, robj] = ctor(alloc_on, SPARTA);
                // only const-reference-based ctor exists.
                // non-mutating call chosen by default.
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_FALSE(robj.isEmpty());

                const auto viewStr = robj.view<StrWrapD>();
                ASSERT_TRUE(viewStr);

                const auto& stdStr = viewStr->get();
                EXPECT_EQ(stdStr.sstr(),
                    (std::string(StrWrapD::struct_) + std::string(SPARTA) +
                        SUFFIX_std_string_clvref + SUFFIX_ctor));
            };
            testCreateOn(rtl::alloc::Heap);
            testCreateOn(rtl::alloc::Stack);
        }
    }
}