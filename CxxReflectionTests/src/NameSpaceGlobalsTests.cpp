
#include <complex>
#include <gtest/gtest.h>

#include "Reflection.h"

using namespace std;
using namespace test_utils;
using namespace rtl::access;


TEST(RTLInterfaceCxxMirror, get_global_types_with_wrong_names)
{
	CxxMirror& cxxMirror = MyReflection::instance();
	optional<Function> noNsFunc = cxxMirror.getFunction("wrong_namespace", "wrong_function");
	EXPECT_FALSE(noNsFunc.has_value());

	optional<Function> noFunc = cxxMirror.getFunction(str_complex, "wrong_function");
	EXPECT_FALSE(noFunc.has_value());

	optional<Function> noFunc0 = cxxMirror.getFunction("wrong_getComplexNumAsString");
	EXPECT_FALSE(noFunc0.has_value());
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
	unique_ptr<RObject> retObj = getMagnitude();
	ASSERT_TRUE(retObj != nullptr);

	optional<double> retVal = retObj->get<double>();
	ASSERT_TRUE(retVal.has_value());

	double magnitude = abs(complex(g_real, g_imaginary));
	EXPECT_DOUBLE_EQ(magnitude, retVal.value());
}


TEST(FunctionInNameSpace, execute_with_wrong_signature)
{
	CxxMirror& cxxMirror = MyReflection::instance();

	optional<Function> rfunc = cxxMirror.getFunction(str_complex, str_setReal);
	ASSERT_TRUE(rfunc.has_value());

	const Function& setReal = rfunc.value();

	EXPECT_TRUE(setReal.hasSignature<double>());
	EXPECT_FALSE(setReal.hasSignature<float>());

	//No op.
	unique_ptr<RObject> retObj = setReal(float(g_real));
	ASSERT_TRUE(retObj == nullptr);
}


TEST(GlobalFunction, get_function_execute_return)
{
	CxxMirror& cxxMirror = MyReflection::instance();

	optional<Function> getFunc = cxxMirror.getFunction(str_getComplexNumAsString);
	ASSERT_TRUE(getFunc.has_value());

	const Function& getComplexNumAsString = getFunc.value();

	unique_ptr<RObject> retObj = getComplexNumAsString();
	ASSERT_TRUE(retObj != nullptr);
	optional<string> retVal = retObj->get<string>();
	ASSERT_TRUE(retVal.has_value());

	string comlexNumStr = to_string(g_real) + "i" + to_string(g_imaginary);
	EXPECT_TRUE(comlexNumStr == retVal.value());
}


TEST(GlobalFunction, overloaded_function_execute_return)
{
	CxxMirror& cxxMirror = MyReflection::instance();

	optional<Function> getFunc = cxxMirror.getFunction(str_reverseString);
	ASSERT_TRUE(getFunc.has_value());

	const Function& reverseString = getFunc.value();

	const char* charStr = STRA;
	unique_ptr<RObject> retObj0 = reverseString(charStr);
	ASSERT_TRUE(retObj0 != nullptr);

	optional<string> retVal0 = retObj0->get<string>();
	ASSERT_TRUE(retVal0.has_value());
	EXPECT_TRUE(retVal0.value() == STRA_REVERSE);

	string stdStr = STRB;
	unique_ptr<RObject> retObj1 = reverseString(stdStr);
	ASSERT_TRUE(retObj1 != nullptr);

	optional<string> retVal1 = retObj1->get<string>();
	ASSERT_TRUE(retVal1.has_value());
	EXPECT_TRUE(retVal1.value() == STRB_REVERSE);

	unique_ptr<RObject> retObj2 = reverseString();
	ASSERT_TRUE(retObj2 != nullptr);

	optional<string> retVal2 = retObj2->get<string>();
	ASSERT_TRUE(retVal2.has_value());
	EXPECT_TRUE(retVal2.value() == REV_STR_VOID_RET);
}