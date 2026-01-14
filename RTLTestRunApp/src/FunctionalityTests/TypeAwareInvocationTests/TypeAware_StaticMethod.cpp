
#include <rtl/rtl_access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringMute.h"
#include "../CxxTestProps/inc/StringConst.h"
#include "../CxxTestProps/inc/StringStatic.h"

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(TypeAware_StaticMethod, init_errors_validation)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::static_method<std::string(char*)> reverse_string = reverseString->argsT<char*>()
                                                                                  .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::SignatureMismatch);
        } {
            rtl::static_method<const char*(std::string)> reverse_string = reverseString->argsT<std::string>()
                                                                                        .returnT<const char*>();
            EXPECT_FALSE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::ReturnTypeMismatch);
        } {
            rtl::static_method<std::string(std::string)> reverse_string = reverseString->argsT<std::string>()
                                                                                        .returnT<std::string>();
            EXPECT_TRUE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::None);
        }
    }


    TEST(TypeAware_StaticMethod, using_wrong_class_n_callable_apis_for_static_method)
    {
        {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);   // has only static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);
            {
                rtl::method<StrStatic, std::string(std::string&)> reverse_string = reverseString.value()
                                                                                                .targetT<StrStatic>()
                                                                                                .argsT<std::string&>()
                                                                                                .returnT<std::string>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::SignatureMismatch);
            } {
                rtl::function<std::string(std::string&)> reverse_string = static_cast<rtl::Function>(reverseString.value())
                                                                                                                  .argsT<std::string&>()
                                                                                                                  .returnT<std::string>();
                EXPECT_FALSE(reverse_string);
                EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidStaticMethodCaller);
            }
        } {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrConst::struct_);   // doesn't have any static-methods.
            ASSERT_TRUE(optStringUtil);

            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
            ASSERT_TRUE(reverseString);

            rtl::static_method<std::string(std::string&)> reverse_string = reverseString.value()
                                                                                        .argsT<std::string&>()
                                                                                        .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
            EXPECT_EQ(reverse_string.get_init_error(), rtl::error::InvalidNonStaticMethodCaller);
        } {
            std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrMute::struct_);   // doesn't have any static-methods.
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


    TEST(TypeAware_StaticMethod, overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil.value().getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::method<StrStatic, std::string(const char)> reverse_string = reverseString.value()
                                                                                          .targetT<StrStatic>()
                                                                                          .argsT<const char>()
                                                                                          .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StrStatic, std::string(char*)> reverse_string = reverseString.value()
                                                                                     .targetT<StrStatic>()
                                                                                     .argsT<char*>()
                                                                                     .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::method<StrStatic, std::string(const char*)> reverse_string = reverseString.value()
                                                                                           .targetT<StrStatic>()
                                                                                           .argsT<const char*>()
                                                                                           .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::const_method<StrStatic, std::string(std::string)> reverse_string = reverseString.value()
                                                                                                 .targetT<const StrStatic>()
                                                                                                 .argsT<std::string>()
                                                                                                 .returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::static_method<std::string(const char*)> reverse_string = reverseString.value()
                                                                                       .argsT<const char*>()
                                                                                       .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRA);
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_const_char_ptr + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string(std::string)> reverse_string = reverseString.value()
                                                                                       .argsT<std::string>()
                                                                                       .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRB);
            auto exp_str = std::string(StrStatic::struct_) + STRB_REVERSE + SUFFIX_std_string + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string()> reverse_string = reverseString.value()
                                                                            .argsT<>()
                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string();
            auto exp_str = std::string(StrStatic::struct_) + REV_STR_VOID_RET + SUFFIX_void + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_StaticMethod, lvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
        ASSERT_TRUE(optStringUtil);

        //non-const target.
        StrMute target;
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

            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_lvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref
            rtl::static_method<std::string(const std::string&)> reverse_string = reverseString.value()
                                                                                              .argsT<const std::string&>()
                                                                                              .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            const std::string lv_str = STRA;
            std::string ret_str = reverse_string(lv_str);
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_clvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument lvalue-ref
            rtl::static_method<std::string(std::string&)> reverse_string = reverseString.value()
                                                                                        .argsT<std::string&>()
                                                                                        .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            std::string lv_str = STRA;
            std::string ret_str = reverse_string(lv_str);

            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_lvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            //argument const-lvalue-ref
            rtl::static_method<std::string(const std::string&)> reverse_string = reverseString.value()
                                                                                              .argsT<const std::string&>()
                                                                                              .returnT<std::string>();
            ASSERT_TRUE(reverse_string);
            //const-target.
            const StrMute& c_target = target;
            std::string lv_str = STRA;

            std::string ret_str = reverse_string(lv_str);

            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_clvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_StaticMethod, rvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::static_method<std::string(std::string&&)> reverse_string = reverseString.value()
                                                                                         .argsT<std::string&&>()
                                                                                         .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRA);
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_rvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_StaticMethod, ptr_and_const_ptr_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
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
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_ptr + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string(const std::string*)> reverse_string = reverseString.value()
                                                                                              .argsT<const std::string*>()
                                                                                              .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(&str);
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_cptr + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_StaticMethod, distinct_functions_with_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
        ASSERT_TRUE(optStringUtil);

        std::string str = STRA;
        {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::static_method<std::string(const std::string_view&)> reverse_string = reverseString.value()
                                                                                                   .argsT<const std::string_view&>()
                                                                                                   .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(str);
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view_clvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrNonConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::static_method<std::string(std::string_view&)> reverse_string = reverseString.value()
                                                                                             .argsT<std::string_view&>()
                                                                                             .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            auto lvstr = std::string_view(str);
            std::string ret_str = reverse_string(lvstr);
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view_lvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrRValueRefArg);
            ASSERT_TRUE(reverseString);

            rtl::static_method<std::string(std::string_view&&)> reverse_string = reverseString.value()
                                                                                              .argsT<std::string_view&&>()
                                                                                              .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(str));
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view_rvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_StaticMethod, overloads_with_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::static_method<std::string(std::string_view)> reverse_string = reverseString.value()
                                                                                            .argsT<std::string_view>()
                                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(STRA));
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string(std::string_view&)> reverse_string = reverseString.value()
                                                                                             .argsT<std::string_view&>()
                                                                                             .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(str);
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view_lvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_StaticMethod, overloads_with_const_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::static_method<std::string(std::string_view)> reverse_string = reverseString.value()
                                                                                            .argsT<std::string_view>()
                                                                                            .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(STRA));
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string(const std::string_view&)> reverse_string = reverseString.value()
                                                                                                   .argsT<const std::string_view&>()
                                                                                                   .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(STRA));
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view_clvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_StaticMethod, overloads_with_ref_and_const_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Record> optStringUtil = cxx::mirror().getRecord(StrStatic::struct_);
        ASSERT_TRUE(optStringUtil);

        std::optional<rtl::Method> reverseString = optStringUtil->getMethod(str_revStrOverloadValRefAndCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::static_method<std::string(std::string_view&)> reverse_string = reverseString.value()
                                                                                             .argsT<std::string_view&>()
                                                                                             .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(str);
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view_lvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::static_method<std::string(const std::string_view&)> reverse_string = reverseString.value()
                                                                                                   .argsT<const std::string_view&>()
                                                                                                   .returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(STRA));
            auto exp_str = std::string(StrStatic::struct_) + STRA_REVERSE + SUFFIX_std_string_view_clvref + SUFFIX_static;
            EXPECT_EQ(ret_str, exp_str);
        }
    }
}