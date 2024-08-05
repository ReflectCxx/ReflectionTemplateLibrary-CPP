
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
		(*setReal)(g_real);

		EXPECT_TRUE(setImaginary->hasSignature<double>());
		(*setImaginary)(g_imaginary);

		EXPECT_TRUE(getMagnitude->hasSignature<>()); //empty template params checks for zero arguments.

		RStatus status = (*getMagnitude)();

		ASSERT_TRUE(status);
		ASSERT_TRUE(status.getReturn().has_value());
		ASSERT_TRUE(status.isOfType<double>());

		double retVal = std::any_cast<double>(status.getReturn());
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

		//different syntax, other than (*setReal)(float(g_real))
		RStatus status = setReal->call(float(g_real));

		ASSERT_FALSE(status);
		ASSERT_FALSE(status.getReturn().has_value());
	}


	TEST(GlobalFunction, get_function_execute_return)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> getComplexNumAsString = cxxMirror.getFunction(str_getComplexNumAsString);
		ASSERT_TRUE(getComplexNumAsString);

		RStatus status = (*getComplexNumAsString)();

		ASSERT_TRUE(status);
		ASSERT_TRUE(status.getReturn().has_value()); 
		ASSERT_TRUE(status.isOfType<string>());

		string retVal = std::any_cast<string>(status.getReturn());
		string comlexNumStr = to_string(g_real) + "i" + to_string(g_imaginary);
		EXPECT_TRUE(comlexNumStr == retVal);
	}


	TEST(GlobalFunction, overloaded_function_execute_return)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> reverseString = cxxMirror.getFunction(str_reverseString);
		ASSERT_TRUE(reverseString);
		{
			RStatus status = (*reverseString)(string(STRA));
			ASSERT_TRUE(status);
			ASSERT_TRUE(status.getReturn().has_value());
			ASSERT_TRUE(status.isOfType<string>());

			string retVal = std::any_cast<string>(status.getReturn());
			EXPECT_TRUE(retVal == STRA_REVERSE);
		} {
			RStatus status = reverseString->call(string(STRB));
			ASSERT_TRUE(status);
			ASSERT_TRUE(status.getReturn().has_value());
			ASSERT_TRUE(status.isOfType<string>());

			string retVal = std::any_cast<string>(status.getReturn());
			EXPECT_TRUE(retVal == STRB_REVERSE);
		} {
			RStatus status = (*reverseString)();
			ASSERT_TRUE(status);
			ASSERT_TRUE(status.getReturn().has_value());
			ASSERT_TRUE(status.isOfType<string>());

			string retVal = std::any_cast<string>(status.getReturn());
			EXPECT_TRUE(retVal == REV_STR_VOID_RET);
		}
	}
}