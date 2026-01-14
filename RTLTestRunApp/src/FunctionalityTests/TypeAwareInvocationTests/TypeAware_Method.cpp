
#include <rtl_access.h>
#include <gtest/gtest.h>

#include <complex>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringMute.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(TypeAware_Method, init_errors_validation)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StrMute, std::string(char*)> reverse_string = reverseString->targetT<StrMute>()
                                                                                   .argsT<char*>()
                                                                                   .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::SignatureMismatch);
        }{
            rtl::method<StrMute, const char*(std::string)> reverse_string = reverseString->targetT<StrMute>()
                                                                                         .argsT<std::string>()
                                                                                         .returnT<const char*>();
            EXPECT_FALSE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::ReturnTypeMismatch);
        } {
            rtl::method<StrMute, std::string(std::string)> reverse_string = reverseString->targetT<StrMute>()
                                                                                         .argsT<std::string>()
                                                                                         .returnT<std::string>();
            EXPECT_TRUE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::None);
        }
    }


    TEST(TypeAware_Method, overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StrMute, std::string(const char)> reverse_string = reverseString->targetT<StrMute>()
                                                                                         .argsT<const char>()
                                                                                         .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StrMute, std::string(char*)> reverse_string = reverseString->targetT<StrMute>()
                                                                                    .argsT<char*>()
                                                                                    .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::const_method<StrMute, std::string(const char*)> reverse_string = reverseString->targetT<const StrMute>()
                                                                                                .argsT<const char*>()
                                                                                                .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::const_method<StrMute, std::string(std::string)> reverse_string = reverseString->targetT<const StrMute>()
                                                                                                .argsT<std::string>()
                                                                                                .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StrMute, std::string(const char*)> reverse_string = reverseString->targetT<StrMute>()
                                                                                          .argsT<const char*>()
                                                                                          .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StrMute())(STRA);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_const_char_ptr;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StrMute, std::string(std::string)> reverse_string = reverseString->targetT<StrMute>()
                                                                                          .argsT<std::string>()
                                                                                          .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StrMute())(STRB);
            auto exp_str = std::string(StrMute::struct_) + STRB_REVERSE + SUFFIX_std_string;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StrMute, std::string()> reverse_string = reverseString->targetT<StrMute>()
                                                                               .argsT<>()
                                                                               .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(StrMute())();
            auto exp_str = std::string(StrMute::struct_) + REV_STR_VOID_RET + SUFFIX_void;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Method, lvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);

        //non-const target.
        StrMute target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            //argument lvalue-ref
            rtl::method<StrMute, std::string(std::string&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                           .argsT<std::string&>()
                                                                                           .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            std::string lv_str = STRA;
            std::string ret_str = reverse_string(target)(lv_str);
            
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_lvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref
            rtl::method<StrMute, std::string(const std::string&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                 .argsT<const std::string&>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            const std::string lv_str = STRA;
            std::string ret_str = reverse_string(target)(lv_str);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_clvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument lvalue-ref
            rtl::method<StrMute, std::string(std::string&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                           .argsT<std::string&>()
                                                                                           .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //const-target.
            const StrMute& c_target = target;
            std::string lv_str = STRA;

            // compile error -
            // std::string ret_str = reverse_string(const_target)(lv_str);
            std::string ret_str = reverse_string(const_cast<StrMute&>(c_target))(lv_str);

            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_lvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref
            rtl::method<StrMute, std::string(const std::string&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                 .argsT<const std::string&>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //const-target.
            const StrMute& c_target = target;
            std::string lv_str = STRA;

            // compile error -
            // std::string ret_str = reverse_string(c_target)(lv_str);
            std::string ret_str = reverse_string(const_cast<StrMute&>(c_target))(lv_str);

            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_clvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Method, rvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);
        
        StrMute target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StrMute, std::string(std::string&&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                            .argsT<std::string&&>()
                                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(STRA);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_rvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StrMute, std::string(const std::string&&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                  .argsT<const std::string&&>()
                                                                                                  .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        }
    }


    TEST(TypeAware_Method, ptr_and_const_ptr_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);

        StrMute target;
        std::string str = STRA;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StrMute, std::string(std::string*)> reverse_string = reverseString->targetT<StrMute>()
                                                                                           .argsT<std::string*>()
                                                                                           .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(&str);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_ptr;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StrMute, std::string(const std::string*)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                 .argsT<const std::string*>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(&str);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_cptr;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Method, distinct_functions_with_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);

        StrMute target;
        std::string str = STRA;
        {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<StrMute, std::string(const std::string_view&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                      .argsT<const std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(str);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view_clvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrNonConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<StrMute, std::string(std::string_view&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                .argsT<std::string_view&>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            auto lvstr = std::string_view(str);
            std::string ret_str = reverse_string(target)(lvstr);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view_lvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrRValueRefArg);
            ASSERT_TRUE(reverseString);

            rtl::method<StrMute, std::string(std::string_view&&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                 .argsT<std::string_view&&>()
                                                                                                 .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(str));
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view_rvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Method, overloads_with_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);

        StrMute target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StrMute, std::string(std::string_view)> reverse_string = reverseString->targetT<StrMute>()
                                                                                               .argsT<std::string_view>()
                                                                                               .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StrMute, std::string(std::string_view&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                .argsT<std::string_view&>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(target)(str);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view_lvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Method, overloads_with_const_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);

        StrMute target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StrMute, std::string(std::string_view)> reverse_string = reverseString->targetT<StrMute>()
                                                                                               .argsT<std::string_view>()
                                                                                               .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StrMute, std::string(const std::string_view&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                      .argsT<const std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view_clvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Method, overloads_with_ref_and_const_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);
        ASSERT_TRUE(optStringUtil);

        StrMute target;
        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValRefAndCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StrMute, std::string(std::string_view&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                .argsT<std::string_view&>()
                                                                                                .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(target)(str);
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view_lvref;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::method<StrMute, std::string(const std::string_view&)> reverse_string = reverseString->targetT<StrMute>()
                                                                                                      .argsT<const std::string_view&>()
                                                                                                      .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(target)(std::string_view(STRA));
            auto exp_str = std::string(StrMute::struct_) + STRA_REVERSE + SUFFIX_std_string_view_clvref;
            EXPECT_EQ(ret_str, exp_str);
        }
    }
}