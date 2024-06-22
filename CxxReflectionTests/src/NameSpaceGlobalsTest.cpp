
#include <complex>
#include <gtest/gtest.h>

#include "Reflection.h"

using namespace std;
using namespace rtl::access;

namespace rtl_tests
{
	double g_img = 9.27;
	double g_real = 3.92;

	TEST(FunctionInNameSpace, GetFunctionObjects)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> noNsFunc = cxxMirror.getFunction("wrong_namespace", "wrong_function");
		EXPECT_FALSE(noNsFunc.has_value());

		optional<Function> noFunc = cxxMirror.getFunction("complex", "wrong_function");
		EXPECT_FALSE(noFunc.has_value());

		optional<Function> rfunc = cxxMirror.getFunction("complex", "setReal");
		EXPECT_TRUE(rfunc.has_value());

		const Function& setReal = rfunc.value();
		EXPECT_TRUE(setReal.getNamespace() == "complex");
		EXPECT_TRUE(setReal.getFunctionName() == "setReal");

		optional<Function> ifunc = cxxMirror.getFunction("complex", "setImaginary");
		EXPECT_TRUE(ifunc.has_value());

		const Function& setImaginary = ifunc.value();
		EXPECT_TRUE(setImaginary.getNamespace() == "complex");
		EXPECT_TRUE(setImaginary.getFunctionName() == "setImaginary");
	}


	TEST(FunctionInNameSpace, ExecuteAndGetReturn)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> magFunc = cxxMirror.getFunction("complex", "getMagnitude");
		EXPECT_TRUE(magFunc.has_value());

		const Function& getMagnitude = magFunc.value();

		Function setReal = cxxMirror.getFunction("complex", "setReal").value();
		Function setImaginary = cxxMirror.getFunction("complex", "setImaginary").value();

		double magnitude = std::abs(std::complex(g_real, g_img));

		setReal(g_real);
		setImaginary(g_img);
		std::unique_ptr<RObject> retObj = getMagnitude();

		EXPECT_TRUE(retObj != nullptr);

		optional<double> retVal = retObj->get<double>();
		EXPECT_TRUE(retVal.has_value());

		EXPECT_DOUBLE_EQ(magnitude, retVal.value());
	}


	TEST(GlobalFunction, GetFunctionObject)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> noFunc = cxxMirror.getFunction("wrong_getComplexNumAsString");
		EXPECT_FALSE(noFunc.has_value());

		optional<Function> getFunc = cxxMirror.getFunction("getComplexNumAsString");
		EXPECT_TRUE(getFunc.has_value());

		const Function& getComplexNumAsString = getFunc.value();

		std::string comlexNumStr = std::to_string(g_real) + "i" + std::to_string(g_img);

		std::unique_ptr<RObject> retObj = getComplexNumAsString();
		EXPECT_TRUE(retObj != nullptr);

		optional<std::string> retVal = retObj->get<std::string>();
		EXPECT_TRUE(retVal.has_value());

		EXPECT_TRUE(comlexNumStr == retVal.value());
	}
}