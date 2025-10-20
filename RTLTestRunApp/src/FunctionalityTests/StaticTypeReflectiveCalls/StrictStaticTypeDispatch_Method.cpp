
#include <complex>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringOps.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(StrictStaticTypeRtl_method, overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StringM, std::string(const char)> reverse_string = reverseString->targetT<StringM>()
                                                                                         .argsT<const char>()
                                                                                         .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StringM, std::string(char*)> reverse_string = reverseString->targetT<StringM>()
                                                                                    .argsT<char*>()
                                                                                    .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<const StringM, std::string(const char*)> reverse_string = reverseString->targetT<const StringM>()
                                                                                                .argsT<const char*>()
                                                                                                .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<const StringM, std::string(std::string)> reverse_string = reverseString->targetT<const StringM>()
                                                                                                .argsT<std::string>()
                                                                                                .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StringM, std::string(const char*)> reverse_string = reverseString->targetT<StringM>()
                                                                                          .argsT<const char*>()
                                                                                          .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StringM())(STRA);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_const_char_ptr;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StringM, std::string(std::string)> reverse_string = reverseString->targetT<StringM>()
                                                                                          .argsT<std::string>()
                                                                                          .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StringM())(STRB);
            auto exp_str = std::string(STRB_REVERSE) + SUFFIX_std_string;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StringM, std::string()> reverse_string = reverseString->targetT<StringM>()
                                                                               .argsT<>()
                                                                               .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StringM())();
            auto exp_str = std::string(REV_STR_VOID_RET) + SUFFIX_void;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_method, lvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);
        ASSERT_TRUE(optStringUtil);

        //non-const target.
        StringM target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            //argument lvalue-ref
            rtl::method<StringM, std::string(std::string&)> reverse_string = reverseString->targetT<StringM>()
                                                                                           .argsT<std::string&>()
                                                                                           .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            std::string lv_str = STRA;
            std::string ret_str = reverse_string(target)(lv_str);
            
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_lvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref
            rtl::method<StringM, std::string(const std::string&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                 .argsT<const std::string&>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            const std::string lv_str = STRA;
            std::string ret_str = reverse_string(target)(lv_str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_clvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument lvalue-ref
            rtl::method<StringM, std::string(std::string&)> reverse_string = reverseString->targetT<StringM>()
                                                                                           .argsT<std::string&>()
                                                                                           .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //const-target.
            const StringM& c_target = target;
            std::string lv_str = STRA;

            // compile error -
            // std::string ret_str = reverse_string(const_target)(lv_str);
            std::string ret_str = reverse_string(const_cast<StringM&>(c_target))(lv_str);

            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_lvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref
            rtl::method<StringM, std::string(const std::string&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                 .argsT<const std::string&>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //const-target.
            const StringM& c_target = target;
            std::string lv_str = STRA;

            // compile error -
            // std::string ret_str = reverse_string(c_target)(lv_str);
            std::string ret_str = reverse_string(const_cast<StringM&>(c_target))(lv_str);

            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_clvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_method, rvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);
        ASSERT_TRUE(optStringUtil);
        
        StringM target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StringM, std::string(std::string&&)> reverse_string = reverseString->targetT<StringM>()
                                                                                            .argsT<std::string&&>()
                                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(STRA);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_rvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StringM, std::string(const std::string&&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                  .argsT<const std::string&&>()
                                                                                                  .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        }
    }


    TEST(StrictStaticTypeRtl_method, ptr_and_const_ptr_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);
        ASSERT_TRUE(optStringUtil);

        StringM target;
        std::string str = STRA;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StringM, std::string(std::string*)> reverse_string = reverseString->targetT<StringM>()
                                                                                           .argsT<std::string*>()
                                                                                           .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(&str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StringM, std::string(const std::string*)> reverse_string = reverseString->targetT<StringM>()
                                                                                                 .argsT<const std::string*>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(&str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_method, distinct_functions_with_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);
        ASSERT_TRUE(optStringUtil);

        StringM target;
        std::string str = STRA;
        {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<StringM, std::string(const std::string_view&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                      .argsT<const std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrNonConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<StringM, std::string(std::string_view&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                .argsT<std::string_view&>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            auto lvstr = std::string_view(str);
            std::string ret_str = reverse_string(target)(lvstr);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrRValueRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<StringM, std::string(std::string_view&&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                 .argsT<std::string_view&&>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(str));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_rvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_method, overloads_with_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);
        ASSERT_TRUE(optStringUtil);

        StringM target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StringM, std::string(std::string_view)> reverse_string = reverseString->targetT<StringM>()
                                                                                               .argsT<std::string_view>()
                                                                                               .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StringM, std::string(std::string_view&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                .argsT<std::string_view&>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(target)(str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_method, overloads_with_const_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);
        ASSERT_TRUE(optStringUtil);

        StringM target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StringM, std::string(std::string_view)> reverse_string = reverseString->targetT<StringM>()
                                                                                               .argsT<std::string_view>()
                                                                                               .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StringM, std::string(const std::string_view&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                      .argsT<const std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_method, overloads_with_ref_and_const_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);
        ASSERT_TRUE(optStringUtil);

        StringM target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValRefAndCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StringM, std::string(std::string_view&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                .argsT<std::string_view&>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(target)(str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StringM, std::string(const std::string_view&)> reverse_string = reverseString->targetT<StringM>()
                                                                                                      .argsT<const std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }
}