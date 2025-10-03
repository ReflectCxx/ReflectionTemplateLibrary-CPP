
#include <complex>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"


using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(StaticTypeQuery, get_namespace_function_types)
    {
        std::optional<rtl::Function> setReal = cxx::mirror().getFunction(str_complex, str_setReal);
        ASSERT_TRUE(setReal);
        {
            EXPECT_TRUE(setReal->getNamespace() == str_complex);
            EXPECT_TRUE(setReal->getFunctionName() == str_setReal);
            {
                rtl::function<void(double)> functor = setReal->to().argsT<double>().returnT<void>();
                ASSERT_TRUE(functor);
            } {
                rtl::function<void(float)> functor = setReal->to().argsT<float>().returnT<void>();
                ASSERT_FALSE(functor);
            }
        }

        std::optional<rtl::Function> setImaginary = cxx::mirror().getFunction(str_complex, str_setImaginary);
        ASSERT_TRUE(setImaginary);
        {
            EXPECT_TRUE(setImaginary->getNamespace() == str_complex);
            EXPECT_TRUE(setImaginary->getFunctionName() == str_setImaginary);
            {
                rtl::function<void(double)> functor = setImaginary->to().argsT<double>().returnT<void>();
                ASSERT_TRUE(functor);
            } {
                rtl::function<char(double)> functor = setImaginary->to().argsT<double>().returnT<char>();
                ASSERT_FALSE(functor);
            }
        }
    }


    TEST(StaticTypeQuery, namespace_function_execute_return)
    {
        std::optional<rtl::Function> getMagnitude = cxx::mirror().getFunction(str_complex, str_getMagnitude);
        ASSERT_TRUE(getMagnitude);

        rtl::function<double()> get_magnitude = getMagnitude->to().argsT().returnT<double>();
        ASSERT_TRUE(get_magnitude);

        std::optional<rtl::Function> setReal = cxx::mirror().getFunction(str_complex, str_setReal);
        ASSERT_TRUE(setReal);

        rtl::function<void(double)> set_real = setReal->to().argsT<double>().returnT<void>();
        ASSERT_TRUE(set_real);

        std::optional<rtl::Function> setImaginary = cxx::mirror().getFunction(str_complex, str_setImaginary);
        ASSERT_TRUE(setImaginary);

        rtl::function<void(double)> set_imaginary = setImaginary->to().argsT<double>().returnT<void>();
        ASSERT_TRUE(set_imaginary);

        set_real(g_real);
        set_imaginary(g_imaginary);
        
        double retVal = get_magnitude();

        double magnitude = abs(std::complex(g_real, g_imaginary));

        EXPECT_DOUBLE_EQ(magnitude, retVal);
    }


    TEST(StaticTypeQuery, global_function_execute_return)
    {
        std::optional<rtl::Function> getComplexNumAsString = cxx::mirror().getFunction(str_getComplexNumAsString);
        ASSERT_TRUE(getComplexNumAsString);
        {
            rtl::function<const std::string()> get_complex_num_as_string = getComplexNumAsString->to().argsT().returnT<const std::string>();
            ASSERT_FALSE(get_complex_num_as_string);
        } {
            rtl::function<std::string&()> get_complex_num_as_string = getComplexNumAsString->to().argsT().returnT<std::string&>();
            ASSERT_FALSE(get_complex_num_as_string);
        } {
            rtl::function<std::string()> get_complex_num_as_string = getComplexNumAsString->to().argsT().returnT<std::string>();
            ASSERT_TRUE(get_complex_num_as_string);

            std::string ret_str = get_complex_num_as_string();

            std::string complex_num_str = std::to_string(g_real) + "i" + std::to_string(g_imaginary);

            EXPECT_EQ(complex_num_str, ret_str);
        }
    }


    //TEST(StaticTypeQuery, overloaded_function_execute_return)
    //{
    //    std::optional<rtl::Function> reverseString = cxx::mirror().getFunction(str_reverseString);
    //    ASSERT_TRUE(reverseString);
    //    {
    //        //STRA's type is 'consexpr const char*', function accepts 'string',
    //        //so type-casting in place as 'string'
    //        auto [err, ret] = reverseString->bind().call(string(STRA));
    //        EXPECT_TRUE(err == rtl::error::None);
    //        ASSERT_FALSE(ret.isEmpty());
    //        EXPECT_TRUE(ret.canViewAs<string>());

    //        string retVal = ret.view<std::string>()->get();
    //        EXPECT_TRUE(retVal == STRA_REVERSE);
    //    } {
    //        //STRB's type is 'consexpr const char*', function accepts 'string',
    //        //so explicitly binding type in template (using bind<...>()) to enforce the type as 'string'.
    //        auto [err, ret] = reverseString->bind<string>().call(STRB);

    //        EXPECT_TRUE(err == rtl::error::None);
    //        ASSERT_FALSE(ret.isEmpty());
    //        EXPECT_TRUE(ret.canViewAs<string>());

    //       string retVal = ret.view<std::string>()->get();
    //       EXPECT_TRUE(retVal == STRB_REVERSE);
    //    } {
    //        auto [err, ret] = reverseString->bind().call();
    //        EXPECT_TRUE(err == rtl::error::None);
    //        ASSERT_FALSE(ret.isEmpty());
    //        EXPECT_TRUE(ret.canViewAs<string>());
    //        
    //        string retVal = ret.view<std::string>()->get();
    //        EXPECT_TRUE(retVal == REV_STR_VOID_RET);
    //    }
    //}


    //TEST(Reflecting_STL_class, std_string__call_reflected_method)
    //{
    //    optional<Record> stdStringClass = cxx::mirror().getRecord("std", "string");
    //    ASSERT_TRUE(stdStringClass);

    //    optional<Method> isStringEmpty = stdStringClass->getMethod("empty");
    //    ASSERT_TRUE(isStringEmpty);

    //    RObject reflected_str0 = rtl::reflect(std::string(""));	//empty string.
    //    {
    //        auto [err, ret] = isStringEmpty->bind(reflected_str0).call();
    //        EXPECT_TRUE(err == rtl::error::None);
    //        ASSERT_FALSE(ret.isEmpty());
    //        EXPECT_TRUE(ret.canViewAs<bool>());
    //        EXPECT_TRUE(ret.view<bool>()->get());
    //    }
    //    RObject reflected_str1 = rtl::reflect(std::string("not_empty"));
    //    {
    //        auto [err, ret] = isStringEmpty->bind(reflected_str1).call();
    //        EXPECT_TRUE(err == rtl::error::None);
    //        ASSERT_FALSE(ret.isEmpty());
    //        EXPECT_TRUE(ret.canViewAs<bool>());
    //        EXPECT_FALSE(ret.view<bool>()->get());
    //    }
    //}


    //TEST(Reflecting_STL_class, std_string_view__call_reflected_method)
    //{
    //    optional<Record> stdStringClass = cxx::mirror().getRecord("std", "string_view");
    //    ASSERT_TRUE(stdStringClass);

    //    optional<Method> isStringEmpty = stdStringClass->getMethod("empty");
    //    ASSERT_TRUE(isStringEmpty);

    //    RObject reflected_str0 = rtl::reflect("");	//empty string.
    //    {
    //        auto [err, ret] = isStringEmpty->bind(reflected_str0).call();
    //        EXPECT_TRUE(err == rtl::error::None);
    //        ASSERT_FALSE(ret.isEmpty());
    //        EXPECT_TRUE(ret.canViewAs<bool>());
    //        EXPECT_TRUE(ret.view<bool>()->get());
    //    }
    //    RObject reflected_str1 = rtl::reflect("not_empty");
    //    {
    //        auto [err, ret] = isStringEmpty->bind(reflected_str1).call();
    //        EXPECT_TRUE(err == rtl::error::None);
    //        ASSERT_FALSE(ret.isEmpty());
    //        EXPECT_TRUE(ret.canViewAs<bool>());
    //        EXPECT_FALSE(ret.view<bool>()->get());
    //    }
    //}
}