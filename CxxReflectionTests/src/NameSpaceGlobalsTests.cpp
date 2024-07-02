
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
			EXPECT_FALSE(badFunc.has_value());
		}
		{
			optional<Function> badFunc = cxxMirror.getFunction(str_complex, "wrong_function");
			EXPECT_FALSE(badFunc.has_value());
		}
		{
			optional<Function> badFunc = cxxMirror.getFunction("wrong_getComplexNumAsString");
			EXPECT_FALSE(badFunc.has_value());
		}
	}


	TEST(FunctionInNameSpace, get_namespace_function_types)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> rfunc = cxxMirror.getFunction(str_complex, str_setReal);
		ASSERT_TRUE(rfunc.has_value());
		optional<Function> ifunc = cxxMirror.getFunction(str_complex, str_setImaginary);
		ASSERT_TRUE(ifunc.has_value());

		const Function& setReal = rfunc.value();
		const Function& setImaginary = ifunc.value();

		EXPECT_TRUE(setReal.getNamespace() == str_complex);
		EXPECT_TRUE(setReal.getFunctionName() == str_setReal);
		EXPECT_TRUE(setImaginary.getNamespace() == str_complex);
		EXPECT_TRUE(setImaginary.getFunctionName() == str_setImaginary);
	}


	TEST(FunctionInNameSpace, namespace_function_execute_return)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> magFunc = cxxMirror.getFunction(str_complex, str_getMagnitude);
		ASSERT_TRUE(magFunc.has_value());

		optional<Function> rfunc = cxxMirror.getFunction(str_complex, str_setReal);
		ASSERT_TRUE(rfunc.has_value());

		optional<Function> ifunc = cxxMirror.getFunction(str_complex, str_setImaginary);
		ASSERT_TRUE(ifunc.has_value());

		const Function& setReal = rfunc.value();
		const Function& setImaginary = ifunc.value();
		const Function& getMagnitude = magFunc.value();

		EXPECT_TRUE(setReal.hasSignature<double>());
		setReal(g_real);

		EXPECT_TRUE(setImaginary.hasSignature<double>());
		setImaginary(g_imaginary);

		EXPECT_TRUE(getMagnitude.hasSignature<void>());

		RStatus callRet = getMagnitude();
		ASSERT_TRUE(callRet.didCallSucceed());

		UniqueAny retObj = callRet.releaseReturn();
		ASSERT_TRUE(retObj.get().has_value() && retObj.isOfType<double>());

		double retVal = std::any_cast<double>(retObj.get());
		double magnitude = abs(complex(g_real, g_imaginary));
		EXPECT_DOUBLE_EQ(magnitude, retVal);
	}


	TEST(FunctionInNameSpace, execute_with_wrong_signature)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> rfunc = cxxMirror.getFunction(str_complex, str_setReal);
		ASSERT_TRUE(rfunc.has_value());

		const Function& setReal = rfunc.value();
		EXPECT_TRUE(setReal.hasSignature<double>());
		EXPECT_FALSE(setReal.hasSignature<float>());

		RStatus callRet = setReal(float(g_real));
		ASSERT_FALSE(callRet.didCallSucceed());

		//No op.
		UniqueAny retObj = callRet.releaseReturn();
		ASSERT_FALSE(retObj.get().has_value());
	}


	TEST(GlobalFunction, get_function_execute_return)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> getFunc = cxxMirror.getFunction(str_getComplexNumAsString);
		ASSERT_TRUE(getFunc.has_value());

		const Function& getComplexNumAsString = getFunc.value();

		RStatus callRet = getComplexNumAsString();
		ASSERT_TRUE(callRet.didCallSucceed());

		UniqueAny retObj = callRet.releaseReturn();
		ASSERT_TRUE(retObj.get().has_value() && retObj.isOfType<string>());

		string retVal = std::any_cast<string>(retObj.get());
		string comlexNumStr = to_string(g_real) + "i" + to_string(g_imaginary);
		EXPECT_TRUE(comlexNumStr == retVal);
	}


	TEST(GlobalFunction, overloaded_function_execute_return)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> getFunc = cxxMirror.getFunction(str_reverseString);
		ASSERT_TRUE(getFunc.has_value());
		const Function& reverseString = getFunc.value();
		{
			RStatus callRet = reverseString(string(STRA));
			ASSERT_TRUE(callRet.didCallSucceed());

			UniqueAny retObj = callRet.releaseReturn();
			ASSERT_TRUE(retObj.get().has_value() && retObj.isOfType<string>());

			string retVal = std::any_cast<string>(retObj.get());
			EXPECT_TRUE(retVal == STRA_REVERSE);
		}
		{
			RStatus callRet = reverseString(string(STRB));
			ASSERT_TRUE(callRet.didCallSucceed());

			UniqueAny retObj = callRet.releaseReturn();
			ASSERT_TRUE(retObj.get().has_value() && retObj.isOfType<string>());

			string retVal = std::any_cast<string>(retObj.get());
			EXPECT_TRUE(retVal == STRB_REVERSE);
		}
		{
			RStatus callRet = reverseString();
			ASSERT_TRUE(callRet.didCallSucceed());

			UniqueAny retObj = callRet.releaseReturn();
			ASSERT_TRUE(retObj.get().has_value() && retObj.isOfType<string>());

			string retVal = std::any_cast<string>(retObj.get());
			EXPECT_TRUE(retVal == REV_STR_VOID_RET);
		}
	}
}