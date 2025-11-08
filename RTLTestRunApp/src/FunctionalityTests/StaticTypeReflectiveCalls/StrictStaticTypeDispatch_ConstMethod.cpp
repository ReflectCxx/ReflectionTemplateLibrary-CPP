
#include <rtl/rtl.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringOps.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(StrictStaticTypeRtl_const_method, std_string_view_method_call_with_known_signature)
    {
        std::optional<rtl::Record> stdStringViewClass = cxx::mirror().getRecord("std", "string_view");
        ASSERT_TRUE(stdStringViewClass);

        std::optional<rtl::Method> isStringEmpty = stdStringViewClass->getMethod("empty");
        ASSERT_TRUE(isStringEmpty);
        {
            rtl::method<std::string_view, bool()> is_empty = isStringEmpty->targetT<std::string_view>()
                                                                           .argsT<>()
                                                                           .returnT<bool>();
            EXPECT_FALSE(is_empty);
        } {
            rtl::method<const std::string_view, bool()> is_empty = isStringEmpty->targetT<const std::string_view>()
                                                                                 .argsT<>()
                                                                                 .returnT<bool>();
            ASSERT_TRUE(is_empty);

            EXPECT_TRUE(is_empty(std::string(""))());

            EXPECT_FALSE(is_empty(std::string("not_empty"))());

            EXPECT_TRUE(is_empty(std::string_view(""))());

            EXPECT_FALSE(is_empty(std::string_view("view_not_empty"))());

            EXPECT_TRUE(is_empty("")());

            EXPECT_FALSE(is_empty("view_not_empty")());
        }
    }


    TEST(StrictStaticTypeRtl_const_method, overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<const StrConst, std::string(const char)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                               .argsT<const char>()
                                                                                               .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<const StrConst, std::string(char*)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                          .argsT<char*>()
                                                                                          .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StrConst, std::string(const char*)> reverse_string = reverseString->targetT<StrConst>()
                                                                                          .argsT<const char*>()
                                                                                          .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StrConst, std::string(std::string)> reverse_string = reverseString->targetT<StrConst>()
                                                                                          .argsT<std::string>()
                                                                                          .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<const StrConst, std::string(const char*)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                .argsT<const char*>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StrConst())(STRA);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_const_char_ptr + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<const StrConst, std::string(std::string)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                .argsT<std::string>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StrConst())(STRB);
            auto exp_str = std::string(STRB_REVERSE) + SUFFIX_std_string + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<const StrConst, std::string()> reverse_string = reverseString->targetT<const StrConst>()
                                                                                     .argsT<>()
                                                                                     .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StrConst())();
            auto exp_str = std::string(REV_STR_VOID_RET) + SUFFIX_void + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_const_method, lvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            //argument lvalue-ref.
            rtl::method<const StrConst, std::string(std::string&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                 .argsT<std::string&>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //non-const target
            StrConst target;
            std::string lv_str = STRA;
            std::string ret_str = reverse_string(target)(lv_str);
            
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_lvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref.
            rtl::method<const StrConst, std::string(const std::string&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                       .argsT<const std::string&>()
                                                                                                       .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //non-const target
            StrConst target;
            const std::string lv_str = STRA;
            std::string ret_str = reverse_string(target)(lv_str);
            
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_clvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument lvalue-ref.
            rtl::method<const StrConst, std::string(std::string&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                 .argsT<std::string&>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //const target.
            const StrConst target;
            std::string lv_str = STRA;
            std::string ret_str = reverse_string(target)(lv_str);
            
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_lvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref.
            rtl::method<const StrConst, std::string(const std::string&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                       .argsT<const std::string&>()
                                                                                                       .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //const target.
            const StrConst target;
            const std::string lv_str = STRA;
            std::string ret_str = reverse_string(target)(lv_str);
            
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_clvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_const_method, rvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);
        ASSERT_TRUE(optStringUtil);
        
        
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<const StrConst, std::string(std::string&&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                  .argsT<std::string&&>()
                                                                                                  .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            {
                //non-const target.
                StrConst target;
                std::string ret_str = reverse_string(target)(STRA);

                auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_rvref + SUFFIX_const;
                EXPECT_EQ(ret_str, exp_str);
            } {
                //const-target
                const StrConst target;
                std::string ret_str = reverse_string(target)(STRA);

                auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_rvref + SUFFIX_const;
                EXPECT_EQ(ret_str, exp_str);
            }
        } {
            rtl::method<const StrConst, std::string(const std::string&&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                        .argsT<const std::string&&>()
                                                                                                        .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        }
    }


    TEST(StrictStaticTypeRtl_const_method, ptr_and_const_ptr_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);
        ASSERT_TRUE(optStringUtil);

        StrConst target;
        std::string str = STRA;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<const StrConst, std::string(std::string*)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                 .argsT<std::string*>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(&str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_ptr + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<const StrConst, std::string(const std::string*)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                       .argsT<const std::string*>()
                                                                                                       .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(&str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_cptr + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_const_method, std_string_method_call_with_known_signature)
    {
        std::optional<rtl::Record> stdStringClass = cxx::mirror().getRecord("std", "string");
        ASSERT_TRUE(stdStringClass);

        std::optional<rtl::Method> isStringEmpty = stdStringClass->getMethod("empty");
        ASSERT_TRUE(isStringEmpty);
        {
            rtl::method<std::string, bool()> is_empty = isStringEmpty->targetT<std::string>()
                                                                      .argsT<>()
                                                                      .returnT<bool>();
            EXPECT_FALSE(is_empty);
        } {
            rtl::method<const std::string, bool()> is_empty = isStringEmpty->targetT<const std::string>()
                                                                            .argsT<>()
                                                                            .returnT<bool>();
            ASSERT_TRUE(is_empty);

            EXPECT_TRUE(is_empty(std::string(""))());

            EXPECT_FALSE(is_empty(std::string("not_empty"))());

            EXPECT_TRUE(is_empty("")());

            EXPECT_FALSE(is_empty("view_not_empty")());
        }
    }


    TEST(StrictStaticTypeRtl_const_method, distinct_functions_with_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);
        ASSERT_TRUE(optStringUtil);

        StrConst target;
        std::string str = STRA;
        {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<const StrConst, std::string(const std::string_view&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                            .argsT<const std::string_view&>()
                                                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            StrConst target;
            std::string ret_str = reverse_string(target)(str);
            
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrNonConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<const StrConst, std::string(std::string_view&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                      .argsT<std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            auto lvstr = std::string_view(str);
            std::string ret_str = reverse_string(target)(lvstr);
            
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrRValueRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<const StrConst, std::string(std::string_view&&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                       .argsT<std::string_view&&>()
                                                                                                       .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(str));
            
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_rvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_const_method, overloads_with_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);
        ASSERT_TRUE(optStringUtil);

        StrConst target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<const StrConst, std::string(std::string_view)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                     .argsT<std::string_view>()
                                                                                                     .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<const StrConst, std::string(std::string_view&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                      .argsT<std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            
            std::string_view str = STRA;
            std::string ret_str = reverse_string(target)(str);

            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_const_method, overloads_with_const_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);
        ASSERT_TRUE(optStringUtil);

        StrConst target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<const StrConst, std::string(std::string_view)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                     .argsT<std::string_view>()
                                                                                                     .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            
            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<const StrConst, std::string(const std::string_view&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                            .argsT<const std::string_view&>()
                                                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeRtl_const_method, overloads_with_ref_and_const_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);
        ASSERT_TRUE(optStringUtil);

        StrConst target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValRefAndCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<const StrConst, std::string(std::string_view&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                      .argsT<std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(target)(str);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_lvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<const StrConst, std::string(const std::string_view&)> reverse_string = reverseString->targetT<const StrConst>()
                                                                                                            .argsT<const std::string_view&>()
                                                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_std_string_view_clvref + SUFFIX_const;
            EXPECT_EQ(ret_str, exp_str);
        }
    }
}