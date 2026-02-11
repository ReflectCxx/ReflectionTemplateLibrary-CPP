
#include <rtl_access.h>
#include <gtest/gtest.h>
#include <complex>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"


using namespace test_utils;


namespace rtl_tests
{
    TEST(TypeAware_Function, init_errors_validation)
    {
        std::optional<rtl::Function> setReal = cxx::mirror().getFunction(cxx::fn::complex::setReal::id);
        ASSERT_TRUE(setReal);
        {
            EXPECT_TRUE(setReal->getFunctionName() == cxx::fn::complex::setReal::id);
            {
                rtl::function<void(double)> functor = setReal->argsT<double>().returnT<void>();
                EXPECT_TRUE(functor);
                EXPECT_EQ(functor.get_init_error(), rtl::error::None);
            } {
                rtl::function<void(float)> functor = setReal->argsT<float>().returnT<void>();
                EXPECT_FALSE(functor);
                EXPECT_EQ(functor.get_init_error(), rtl::error::SignatureMismatch);
            }
        }

        std::optional<rtl::Function> setImaginary = cxx::mirror().getFunction(cxx::fn::complex::setImaginary::id);
        ASSERT_TRUE(setImaginary);
        {
            EXPECT_TRUE(setImaginary->getFunctionName() == cxx::fn::complex::setImaginary::id);
            {
                rtl::function<void(double)> functor = setImaginary->argsT<double>().returnT<void>();
                EXPECT_TRUE(functor);
                EXPECT_EQ(functor.get_init_error(), rtl::error::None);
            } {
                rtl::function<char(double)> functor = setImaginary->argsT<double>().returnT<char>();
                EXPECT_FALSE(functor);
                EXPECT_EQ(functor.get_init_error(), rtl::error::ReturnTypeMismatch);
            }
        }
    }


    TEST(TypeAware_Function, namespace_fn_call_with_known_signature)
    {
        std::optional<rtl::Function> getMagnitude = cxx::mirror().getFunction(cxx::fn::complex::getMagnitude::id);
        ASSERT_TRUE(getMagnitude);

        rtl::function<double()> get_magnitude = getMagnitude->argsT<>().returnT<double>();
        ASSERT_TRUE(get_magnitude);

        std::optional<rtl::Function> setReal = cxx::mirror().getFunction(cxx::fn::complex::setReal::id);
        ASSERT_TRUE(setReal);

        rtl::function<void(double)> set_real = setReal->argsT<double>().returnT<void>();
        ASSERT_TRUE(set_real);

        std::optional<rtl::Function> setImaginary = cxx::mirror().getFunction(cxx::fn::complex::setImaginary::id);
        ASSERT_TRUE(setImaginary);

        rtl::function<void(double)> set_imaginary = setImaginary->argsT<double>().returnT<void>();
        ASSERT_TRUE(set_imaginary);

        set_real(g_real);
        set_imaginary(g_imaginary);
        
        double retVal = get_magnitude();

        double magnitude = abs(std::complex(g_real, g_imaginary));

        EXPECT_DOUBLE_EQ(magnitude, retVal);
    }


    TEST(TypeAware_Function, global_fn_call_with_known_signature)
    {
        std::optional<rtl::Function> getComplexNumStr = cxx::mirror().getFunction(cxx::fn::getComplexNumAsString::id);
        ASSERT_TRUE(getComplexNumStr);
        {
            rtl::function<const std::string()> get_complex_num_str = getComplexNumStr->argsT<>().returnT<const std::string>();
            EXPECT_FALSE(get_complex_num_str);
        } {
            rtl::function<std::string&()> get_complex_num_str = getComplexNumStr->argsT<>().returnT<std::string&>();
            EXPECT_FALSE(get_complex_num_str);
        } {
            rtl::function<std::string()> get_complex_num_str = getComplexNumStr->argsT<>().returnT<std::string>();
            ASSERT_TRUE(get_complex_num_str);

            std::string ret_str = get_complex_num_str();

            std::string complex_num_str = std::to_string(g_real) + "i" + std::to_string(g_imaginary);

            EXPECT_EQ(complex_num_str, ret_str);
        }
    }


    TEST(TypeAware_Function, overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::function<std::string(const char)> reverse_string = reverseString->argsT<const char>().returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::function<std::string(char*)> reverse_string = reverseString->argsT<char*>().returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        } {
            rtl::function<std::string(const char*)> reverse_string = reverseString->argsT<const char*>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRA.data());
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_const_char_ptr);
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(std::string)> reverse_string = reverseString->argsT<std::string>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRB.data());
            auto exp_str = std::string(STRB_REVERSE).append(SUFFIX_std_string);
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string()> reverse_string = reverseString->argsT<>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string();
            auto exp_str = std::string(REV_STR_VOID_RET).append(SUFFIX_void);
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Function, lvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::function<std::string(std::string&)> reverse_string = reverseString->argsT<std::string&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string lv_str(STRA);
            std::string ret_str = reverse_string(lv_str);
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_lvref);
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(const std::string&)> reverse_string = reverseString->argsT<const std::string&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            const std::string lv_str(STRA);
            std::string ret_str = reverse_string(lv_str);
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_clvref);
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Function, rvalue_ref_overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::function<std::string(std::string&&)> reverse_string = reverseString->argsT<std::string&&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRA.data());
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_rvref);
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(const std::string&&)> reverse_string = reverseString->argsT<const std::string&&>().returnT<std::string>();
            EXPECT_FALSE(reverse_string);
        }
    }


    TEST(TypeAware_Function, ptr_and_const_ptr_overload_resolution_with_known_signatures)
    {
        std::string str(STRA);
        std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::function<std::string(std::string*)> reverse_string = reverseString->argsT<std::string*>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(&str);
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_ptr);
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(const std::string*)> reverse_string = reverseString->argsT<const std::string*>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(&str);
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_cptr);
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Function, distinct_functions_with_ref_args_call_with_known_signature)
    {
        std::string str(STRA);
        {
            std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_revStrConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::function<std::string(const std::string_view&)> reverse_string = reverseString->argsT<const std::string_view&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(str);
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view_clvref);
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_revStrNonConstRefArg);
            ASSERT_TRUE(reverseString);

            rtl::function<std::string(std::string_view&)> reverse_string = reverseString->argsT<std::string_view&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            auto lvstr = std::string_view(str);
            std::string ret_str = reverse_string(lvstr);
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view_lvref);
            EXPECT_EQ(ret_str, exp_str);
        } {
            std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_revStrRValueRefArg);
            ASSERT_TRUE(reverseString);

            rtl::function<std::string(std::string_view&&)> reverse_string = reverseString->argsT<std::string_view&&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(str));
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view_rvref);
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Function, overloads_with_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_revStrOverloadValRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::function<std::string(std::string_view)> reverse_string = reverseString->argsT<std::string_view>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view);
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(std::string_view&)> reverse_string = reverseString->argsT<std::string_view&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(str);
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view_lvref);
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Function, overloads_with_const_ref_and_value_args_call_with_known_signature)
    {
        std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_revStrOverloadValCRef);
        ASSERT_TRUE(reverseString);
        {
            rtl::function<std::string(std::string_view)> reverse_string = reverseString->argsT<std::string_view>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view);
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(const std::string_view&)> reverse_string = reverseString->argsT<const std::string_view&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view_clvref);
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(TypeAware_Function, overloads_with_ref_and_const_ref_args_call_with_known_signature)
    {
        std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(cxx::type::StrConst::fn::revStrOverloadRefAndCRef::id);
        ASSERT_TRUE(reverseString);
        {
            rtl::function<std::string(std::string_view&)> reverse_string = reverseString->argsT<std::string_view&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string_view str = STRA;
            std::string ret_str = reverse_string(str);
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view_lvref);
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(const std::string_view&)> reverse_string = reverseString->argsT<const std::string_view&>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(std::string_view(STRA));
            auto exp_str = std::string(STRA_REVERSE).append(SUFFIX_std_string_view_clvref);
            EXPECT_EQ(ret_str, exp_str);
        }
    }
}