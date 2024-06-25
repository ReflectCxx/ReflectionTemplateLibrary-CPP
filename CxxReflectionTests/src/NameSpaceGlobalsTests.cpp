
#include <complex>
#include <gtest/gtest.h>

#include "Reflection.h"

using namespace std;
using namespace rtl::access;

static constexpr double g_img = 9.27;
static constexpr double g_real = 3.92;

TEST(FunctionInNameSpace, get_namespace_function_objects)
{
	CxxMirror& cxxMirror = MyReflection::instance();

	optional<Function> noNsFunc = cxxMirror.getFunction("wrong_namespace", "wrong_function");
	EXPECT_FALSE(noNsFunc.has_value());
	optional<Function> noFunc = cxxMirror.getFunction("complex", "wrong_function");
	EXPECT_FALSE(noFunc.has_value());
	optional<Function> rfunc = cxxMirror.getFunction("complex", "setReal");
	ASSERT_TRUE(rfunc.has_value());
	optional<Function> ifunc = cxxMirror.getFunction("complex", "setImaginary");
	ASSERT_TRUE(ifunc.has_value());

	const Function& setReal = rfunc.value();
	const Function& setImaginary = ifunc.value();

	EXPECT_TRUE(setReal.getNamespace() == "complex");
	EXPECT_TRUE(setReal.getFunctionName() == "setReal");
	EXPECT_TRUE(setImaginary.getNamespace() == "complex");
	EXPECT_TRUE(setImaginary.getFunctionName() == "setImaginary");
}


TEST(FunctionInNameSpace, namespace_function_execute_return)
{
	CxxMirror& cxxMirror = MyReflection::instance();

	optional<Function> magFunc = cxxMirror.getFunction("complex", "getMagnitude");
	ASSERT_TRUE(magFunc.has_value());
	optional<Function> rfunc = cxxMirror.getFunction("complex", "setReal");
	ASSERT_TRUE(rfunc.has_value());
	optional<Function> ifunc = cxxMirror.getFunction("complex", "setImaginary");
	ASSERT_TRUE(ifunc.has_value());

	const Function& setReal = rfunc.value();
	const Function& setImaginary = ifunc.value();
	const Function& getMagnitude = magFunc.value();

	EXPECT_TRUE(setReal.hasSignature<double>());
	setReal(g_real);

	EXPECT_TRUE(setImaginary.hasSignature<double>());
	setImaginary(g_img);

	EXPECT_TRUE(getMagnitude.hasSignature<void>());
	unique_ptr<RObject> retObj = getMagnitude();
	ASSERT_TRUE(retObj != nullptr);

	optional<double> retVal = retObj->get<double>();
	ASSERT_TRUE(retVal.has_value());

	double magnitude = abs(complex(g_real, g_img));
	EXPECT_DOUBLE_EQ(magnitude, retVal.value());
}


TEST(FunctionInNameSpace, execute_with_wrong_signature)
{
	CxxMirror& cxxMirror = MyReflection::instance();

	optional<Function> rfunc = cxxMirror.getFunction("complex", "setReal");
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

	optional<Function> noFunc = cxxMirror.getFunction("wrong_getComplexNumAsString");
	EXPECT_FALSE(noFunc.has_value());
	optional<Function> getFunc = cxxMirror.getFunction("getComplexNumAsString");
	ASSERT_TRUE(getFunc.has_value());

	const Function& getComplexNumAsString = getFunc.value();

	unique_ptr<RObject> retObj = getComplexNumAsString();
	ASSERT_TRUE(retObj != nullptr);
	optional<string> retVal = retObj->get<string>();
	ASSERT_TRUE(retVal.has_value());

	string comlexNumStr = to_string(g_real) + "i" + to_string(g_img);
	EXPECT_TRUE(comlexNumStr == retVal.value());
}


TEST(GlobalFunction, overloaded_function_execute_return)
{
	CxxMirror& cxxMirror = MyReflection::instance();

	optional<Function> getFunc = cxxMirror.getFunction("reverseString");
	ASSERT_TRUE(getFunc.has_value());

	const Function& reverseString = getFunc.value();

	const char* charStr = "ReflectC++";
	unique_ptr<RObject> retObj0 = reverseString(charStr);
	ASSERT_TRUE(retObj0 != nullptr);

	optional<string> retVal0 = retObj0->get<string>();
	ASSERT_TRUE(retVal0.has_value());
	EXPECT_TRUE(retVal0.value() == "++CtcelfeR");

	string stdStr = "cxxReflection";
	unique_ptr<RObject> retObj1 = reverseString(stdStr);
	ASSERT_TRUE(retObj1 != nullptr);

	optional<string> retVal1 = retObj1->get<string>();
	ASSERT_TRUE(retVal1.has_value());
	EXPECT_TRUE(retVal1.value() == "noitcelfeRxxc");
}