
#include <complex>
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsGlobals.h"

using namespace std;
using namespace test_utils;
using namespace rtl::access;

namespace rtl_tests 
{
	TEST(RTLInterfaceCxxMirror, get_global_functions_with_wrong_names)
	{
		CxxMirror& cxxMirror = MyReflection::instance();
		{
			optional<Function> badFunc = cxxMirror.getFunction("wrong_namespace", "wrong_function");
			EXPECT_FALSE(badFunc);
		} {
			optional<Function> badFunc = cxxMirror.getFunction(str_complex, "wrong_function");
			EXPECT_FALSE(badFunc);
		} {
			optional<Function> badFunc = cxxMirror.getFunction("wrong_getComplexNumAsString");
			EXPECT_FALSE(badFunc);
		}
	}


	TEST(FunctionInNameSpace, get_namespace_function_types)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> setReal = cxxMirror.getFunction(str_complex, str_setReal);
		ASSERT_TRUE(setReal);

		optional<Function> setImaginary = cxxMirror.getFunction(str_complex, str_setImaginary);
		ASSERT_TRUE(setImaginary);

		EXPECT_TRUE(setReal->getNamespace() == str_complex);
		EXPECT_TRUE(setReal->getFunctionName() == str_setReal);
		EXPECT_TRUE(setImaginary->getNamespace() == str_complex);
		EXPECT_TRUE(setImaginary->getFunctionName() == str_setImaginary);
	}


	TEST(FunctionInNameSpace, namespace_function_execute_return)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> getMagnitude = cxxMirror.getFunction(str_complex, str_getMagnitude);
		ASSERT_TRUE(getMagnitude);

		optional<Function> setReal = cxxMirror.getFunction(str_complex, str_setReal);
		ASSERT_TRUE(setReal);

		optional<Function> setImaginary = cxxMirror.getFunction(str_complex, str_setImaginary);
		ASSERT_TRUE(setImaginary);

		EXPECT_TRUE(setReal->hasSignature<double>());

		double real = g_real;	//g_real's type is "const double", so can't be passed directly to setReal else,
								//its type will be inferred 'const double' instead of 'double'.
		auto [err0, ret0] = (*setReal)(real);
		ASSERT_TRUE(err0 == rtl::error::None);
		EXPECT_TRUE(ret0.isEmpty());

		EXPECT_TRUE(setImaginary->hasSignature<double>());

		double imaginary = g_imaginary;	//g_imaginary's type is "const double", so can't be passed directly to setImaginary else,
										//its type will be inferred 'const double' instead of 'double'.
		auto [err1, ret1] = (*setImaginary)(imaginary);
		ASSERT_TRUE(err1 == rtl::error::None);
		EXPECT_TRUE(ret1.isEmpty());

		EXPECT_TRUE(getMagnitude->hasSignature<>()); //empty template params checks for zero arguments.

		auto [err2, ret2] = (*getMagnitude)();

		ASSERT_TRUE(err2 == rtl::error::None);
		ASSERT_TRUE(!ret2.isEmpty());
		ASSERT_TRUE(ret2.canViewAs<double>());

		double retVal = ret2.view<double>()->get();
		double magnitude = abs(complex(g_real, g_imaginary));
		EXPECT_DOUBLE_EQ(magnitude, retVal);
	}


	TEST(FunctionInNameSpace, execute_with_wrong_signature)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> setReal = cxxMirror.getFunction(str_complex, str_setReal);
		ASSERT_TRUE(setReal);

		EXPECT_TRUE(setReal->hasSignature<double>());

		EXPECT_FALSE(setReal->hasSignature<float>());

		//g_real's type is "const double", so can't be passed directly to setReal.
		//Instead we can explicitly specify the types as template parameter,
		//like, (*setReal).operator()<float>(g_real);
		//or we can use the bind<...>().call(), specifying type as template param, like,
		auto [err, robj] = setReal->bind<float>().call(g_real);

		ASSERT_TRUE(err == rtl::error::SignatureMismatch);
		ASSERT_TRUE(robj.isEmpty());
	}


	TEST(GlobalFunction, get_function_execute_return)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> getComplexNumAsString = cxxMirror.getFunction(str_getComplexNumAsString);
		ASSERT_TRUE(getComplexNumAsString);

		auto [err, ret] = (*getComplexNumAsString)();

		ASSERT_TRUE(err == rtl::error::None);
		ASSERT_FALSE(ret.isEmpty());
		ASSERT_TRUE(ret.canViewAs<string>());

		string retVal = ret.view<std::string>()->get();
		string comlexNumStr = to_string(g_real) + "i" + to_string(g_imaginary);
		EXPECT_TRUE(comlexNumStr == retVal);
	}


	TEST(GlobalFunction, overloaded_function_execute_return)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> reverseString = cxxMirror.getFunction(str_reverseString);
		ASSERT_TRUE(reverseString);
		{
			//STRA's type is 'consexpr const char*', function accepts 'string',
			//so type-casting in place as 'string'
			auto [err, ret] = (*reverseString)(string(STRA));
			ASSERT_TRUE(err == rtl::error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			string retVal = ret.view<std::string>()->get();
			EXPECT_TRUE(retVal == STRA_REVERSE);
		} {
			//STRB's type is 'consexpr const char*', function accepts 'string',
			//so explicitly binding type in template (using bind<...>()) to enforce the type as 'string'.
			auto [err, ret] = reverseString->bind<string>().call(STRB);

			ASSERT_TRUE(err == rtl::error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			string retVal = ret.view<std::string>()->get();
			EXPECT_TRUE(retVal == STRB_REVERSE);
		} {
			auto [err, ret] = (*reverseString)();
			ASSERT_TRUE(err == rtl::error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			string retVal = ret.view<std::string>()->get();
			EXPECT_TRUE(retVal == REV_STR_VOID_RET);
		}
	}
}