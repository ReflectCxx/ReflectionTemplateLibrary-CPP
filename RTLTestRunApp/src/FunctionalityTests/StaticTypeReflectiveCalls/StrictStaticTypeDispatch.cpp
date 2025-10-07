
#include <complex>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"


using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(StrictStaticTypeDispatch, namespace_function_validation_with_known_signature)
    {
        std::optional<rtl::Function> setReal = cxx::mirror().getFunction(str_complex, str_setReal);
        ASSERT_TRUE(setReal);
        {
            EXPECT_TRUE(setReal->getNamespace() == str_complex);
            EXPECT_TRUE(setReal->getFunctionName() == str_setReal);
            {
                rtl::function<void(double)> functor = setReal->argsT<double>().returnT<void>();
                ASSERT_TRUE(functor);
            } {
                rtl::function<void(float)> functor = setReal->argsT<float>().returnT<void>();
                ASSERT_FALSE(functor);
            }
        }

        std::optional<rtl::Function> setImaginary = cxx::mirror().getFunction(str_complex, str_setImaginary);
        ASSERT_TRUE(setImaginary);
        {
            EXPECT_TRUE(setImaginary->getNamespace() == str_complex);
            EXPECT_TRUE(setImaginary->getFunctionName() == str_setImaginary);
            {
                rtl::function<void(double)> functor = setImaginary->argsT<double>().returnT<void>();
                ASSERT_TRUE(functor);
            } {
                rtl::function<char(double)> functor = setImaginary->argsT<double>().returnT<char>();
                ASSERT_FALSE(functor);
            }
        }
    }


    TEST(StrictStaticTypeDispatch, namespace_function_call_with_known_signature)
    {
        std::optional<rtl::Function> getMagnitude = cxx::mirror().getFunction(str_complex, str_getMagnitude);
        ASSERT_TRUE(getMagnitude);

        rtl::function<double()> get_magnitude = getMagnitude->argsT<>().returnT<double>();
        ASSERT_TRUE(get_magnitude);

        std::optional<rtl::Function> setReal = cxx::mirror().getFunction(str_complex, str_setReal);
        ASSERT_TRUE(setReal);

        rtl::function<void(double)> set_real = setReal->argsT<double>().returnT<void>();
        ASSERT_TRUE(set_real);

        std::optional<rtl::Function> setImaginary = cxx::mirror().getFunction(str_complex, str_setImaginary);
        ASSERT_TRUE(setImaginary);

        rtl::function<void(double)> set_imaginary = setImaginary->argsT<double>().returnT<void>();
        ASSERT_TRUE(set_imaginary);

        set_real(g_real);
        set_imaginary(g_imaginary);
        
        double retVal = get_magnitude();

        double magnitude = abs(std::complex(g_real, g_imaginary));

        EXPECT_DOUBLE_EQ(magnitude, retVal);
    }


    TEST(StrictStaticTypeDispatch, global_function_call_with_known_signature)
    {
        std::optional<rtl::Function> getComplexNumStr = cxx::mirror().getFunction(str_getComplexNumAsString);
        ASSERT_TRUE(getComplexNumStr);
        {
            rtl::function<const std::string()> get_complex_num_str = getComplexNumStr->argsT<>().returnT<const std::string>();
            ASSERT_FALSE(get_complex_num_str);
        } {
            rtl::function<std::string&()> get_complex_num_str = getComplexNumStr->argsT<>().returnT<std::string&>();
            ASSERT_FALSE(get_complex_num_str);
        } {
            rtl::function<std::string()> get_complex_num_str = getComplexNumStr->argsT<>().returnT<std::string>();
            ASSERT_TRUE(get_complex_num_str);

            std::string ret_str = get_complex_num_str();

            std::string complex_num_str = std::to_string(g_real) + "i" + std::to_string(g_imaginary);

            EXPECT_EQ(complex_num_str, ret_str);
        }
    }


    TEST(StrictStaticTypeDispatch, overload_resolution_with_known_signatures)
    {
        std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_reverseString);
        ASSERT_TRUE(reverseString);
        {
            rtl::function<std::string(const char)> reverse_string = reverseString->argsT<const char>().returnT<std::string>();
            ASSERT_FALSE(reverse_string);
        } {
            rtl::function<std::string(char*)> reverse_string = reverseString->argsT<char*>().returnT<std::string>();
            ASSERT_FALSE(reverse_string);
        } {
            rtl::function<std::string(const char*)> reverse_string = reverseString->argsT<const char*>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRA);
            auto exp_str = std::string(STRA_REVERSE) + SUFFIX_ARG_const_char_ptr;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string(std::string)> reverse_string = reverseString->argsT<std::string>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string(STRB);
            auto exp_str = std::string(STRB_REVERSE) + SUFFIX_ARG_std_string;
            EXPECT_EQ(ret_str, exp_str);
        } {
            rtl::function<std::string()> reverse_string = reverseString->argsT<>().returnT<std::string>();
            ASSERT_TRUE(reverse_string);

            std::string ret_str = reverse_string();
            auto exp_str = std::string(REV_STR_VOID_RET) + SUFFIX_ARG_void;
            EXPECT_EQ(ret_str, exp_str);
        }
    }


    TEST(StrictStaticTypeDispatch, std_string_method_call_with_known_signature)
    {
        std::optional<rtl::Record> stdStringClass = cxx::mirror().getRecord("std", "string");
        ASSERT_TRUE(stdStringClass);

        std::optional<rtl::Method> isStringEmpty = stdStringClass->getMethod("empty");
        ASSERT_TRUE(isStringEmpty);
        {
            rtl::method<bool(std::string::*)()> is_empty = isStringEmpty->recordT<std::string>().argsT<>().returnT<bool>();
            ASSERT_FALSE(is_empty);
        } {
            rtl::method<bool(std::string::*)() const> is_empty = isStringEmpty->recordT<const std::string>().argsT<>().returnT<bool>();
            ASSERT_TRUE(is_empty);

            EXPECT_TRUE(is_empty(std::string("")));

            EXPECT_FALSE(is_empty(std::string("not_empty")));

            EXPECT_TRUE(is_empty(""));

            EXPECT_FALSE(is_empty("view_not_empty"));
        }
    }


    TEST(StrictStaticTypeDispatch, std_string_view_method_call_with_known_signature)
    {
        std::optional<rtl::Record> stdStringViewClass = cxx::mirror().getRecord("std", "string_view");
        ASSERT_TRUE(stdStringViewClass);

        std::optional<rtl::Method> isStringEmpty = stdStringViewClass->getMethod("empty");
        ASSERT_TRUE(isStringEmpty);
        {
            rtl::method<bool(std::string_view::*)()> is_empty = isStringEmpty->recordT<std::string_view>().argsT<>().returnT<bool>();
            ASSERT_FALSE(is_empty);
        } {
            rtl::method<bool(std::string_view::*)() const> is_empty = isStringEmpty->recordT<const std::string_view>().argsT<>().returnT<bool>();
            ASSERT_TRUE(is_empty);

            EXPECT_TRUE(is_empty(std::string("")));

            EXPECT_FALSE(is_empty(std::string("not_empty")));

            EXPECT_TRUE(is_empty(std::string_view("")));

            EXPECT_FALSE(is_empty(std::string_view("view_not_empty")));

            EXPECT_TRUE(is_empty(""));

            EXPECT_FALSE(is_empty("view_not_empty"));
        }
    }
}