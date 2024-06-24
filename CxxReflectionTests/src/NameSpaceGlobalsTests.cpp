
#include <complex>
#include <gtest/gtest.h>

#include "Reflection.h"

using namespace std;
using namespace rtl::access;

static constexpr double g_img = 9.27;
static constexpr double g_real = 3.92;

TEST(FunctionInNameSpace, GetFunctionObjects)
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


TEST(FunctionInNameSpace, ExecuteAndGetReturn)
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


TEST(GlobalFunction, GetFunctionObject)
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


TEST(FunctionInNameSpace, ExecuteWithWrongParams)
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