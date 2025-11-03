
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringOps.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(StrictStaticTypeRtl_static_method, using_wrong_class_n_callable_apis_for_static_method)
    {
        {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringS::struct_);   // has only static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);
            {
                rtl::method<StringS, std::string(std::string&)> reverse_string = reverseString.value()
                                                                                              .targetT<StringS>()
                                                                                              .argsT<std::string&>()
                                                                                              .returnT<std::string>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidStaticMethodCaller);
            } {
                rtl::function<std::string(std::string&)> reverse_string = static_cast<rtl::Function>(reverseString.value())
                                                                                                                  .argsT<std::string&>()
                                                                                                                  .returnT<std::string>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidStaticMethodCaller);
            }
        } {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringC::struct_);   // doesn't have any static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);

            rtl::static_method<std::string(std::string&)> reverse_string = reverseString.value()
                                                                                        .argsT<std::string&>()
                                                                                        .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidNonStaticMethodCaller);
        } {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringM::struct_);   // doesn't have any static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);
            {
                rtl::static_method<std::string(std::string&)> reverse_string = reverseString.value()
                                                                                            .argsT<std::string&>()
                                                                                            .returnT<std::string>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidNonStaticMethodCaller);
            }
        }
    }


    TEST(StrictStaticTypeRtl_static_method, overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringS::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil.value().getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StringS, std::string(const char)> reverse_string = reverseString.value()
                                                                                        .targetT<StringS>()
                                                                                        .argsT<const char>()
                                                                                        .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StringS, std::string(char*)> reverse_string = reverseString.value()
                                                                                   .targetT<StringS>()
                                                                                   .argsT<char*>()
                                                                                   .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StringS, std::string(const char*)> reverse_string = reverseString.value()
                                                                                         .targetT<StringS>()
                                                                                         .argsT<const char*>()
                                                                                         .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<const StringS, std::string(std::string)> reverse_string = reverseString.value()
                                                                                               .targetT<const StringS>()
                                                                                               .argsT<std::string>()
                                                                                               .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::static_method<std::string(const char*)> reverse_string = reverseString.value()
                                                                                       .argsT<const char*>()
                                                                                       .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRA);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_const_char_ptr + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string(std::string)> reverse_string = reverseString.value()
                                                                                       .argsT<std::string>()
                                                                                       .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRB);
            auto exp_str = std::string(STRB_REVERSE) + SUFFIX_std_string + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string()> reverse_string = reverseString.value()
                                                                            .argsT<>()
                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string();
            auto exp_str = std::string(REV_STR_VOID_RET) + SUFFIX_void + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_static_method, lvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringS::struct_);
        ASSERT_TRUE(optStringUtil);

        //non-const target.
        StringM target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            //argument lvalue-ref
            rtl::static_method<std::string(std::string&)> reverse_string = reverseString.value()
                                                                                        .argsT<std::string&>()
                                                                                        .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            std::string lv_str = STRA;
            std::string ret_str = reverse_string(lv_str);

            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_lvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref
            rtl::static_method<std::string(const std::string&)> reverse_string = reverseString.value()
                                                                                              .argsT<const std::string&>()
                                                                                              .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            const std::string lv_str = STRA;
            std::string ret_str = reverse_string(lv_str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_clvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument lvalue-ref
            rtl::static_method<std::string(std::string&)> reverse_string = reverseString.value()
                                                                                        .argsT<std::string&>()
                                                                                        .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            std::string lv_str = STRA;
            std::string ret_str = reverse_string(lv_str);

            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_lvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref
            rtl::static_method<std::string(const std::string&)> reverse_string = reverseString.value()
                                                                                              .argsT<const std::string&>()
                                                                                              .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //const-target.
            const StringM& c_target = target;
            std::string lv_str = STRA;

            std::string ret_str = reverse_string(lv_str);

            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_clvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_static_method, rvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringS::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::static_method<std::string(std::string&&)> reverse_string = reverseString.value()
                                                                                         .argsT<std::string&&>()
                                                                                         .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRA);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_rvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_static_method, ptr_and_const_ptr_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StringS::struct_);
        ASSERT_TRUE(optStringUtil);

        std::string str = STRA;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::static_method<std::string(std::string*)> reverse_string = reverseString.value()
                                                                                        .argsT<std::string*>()
                                                                                        .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(&str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string(const std::string*)> reverse_string = reverseString.value()
                                                                                                .argsT<const std::string*>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(&str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }
}