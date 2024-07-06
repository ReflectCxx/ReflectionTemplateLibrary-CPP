#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(StaticMethodTest, unique_method_call)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_getDefaults);
			ASSERT_TRUE(methOpt.has_value());

			const Method& getDefaults = methOpt.value();
			ASSERT_TRUE(getDefaults.hasSignature<void>());

			const RStatus& callRet = getDefaults()();
			ASSERT_TRUE(callRet.didCallSucceed());

			const UniqueAny& retVal = callRet.releaseReturn();
			ASSERT_TRUE(retVal.get().has_value() && retVal.isOfType<string>());

			const string& retStr = any_cast<string>(retVal.get());
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(StaticMethodTest, overload_method_void_call)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_getProfile);
			ASSERT_TRUE(methOpt.has_value());

			const Method& getProfile = methOpt.value();
			ASSERT_TRUE(getProfile.hasSignature<void>());

			const RStatus& callRet = getProfile()();
			ASSERT_TRUE(callRet.didCallSucceed());

			const UniqueAny& retVal = callRet.releaseReturn();
			ASSERT_TRUE(retVal.get().has_value() && retVal.isOfType<string>());

			const string& retStr = any_cast<string>(retVal.get());
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile());
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(StaticMethodTest, overload_method_args_bool_call)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_getProfile);
			ASSERT_TRUE(methOpt.has_value());

			const Method& getProfile = methOpt.value();
			ASSERT_TRUE(getProfile.hasSignature<bool>());

			{
				const RStatus& callRet = getProfile()(true);
				ASSERT_TRUE(callRet.didCallSucceed());

				const UniqueAny& retVal = callRet.releaseReturn();
				ASSERT_TRUE(retVal.get().has_value() && retVal.isOfType<string>());

				const string& retStr = any_cast<string>(retVal.get());
				EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(true));

			}
			{
				const RStatus& callRet = getProfile()(false);
				ASSERT_TRUE(callRet.didCallSucceed());

				const UniqueAny& retVal = callRet.releaseReturn();
				ASSERT_TRUE(retVal.get().has_value() && retVal.isOfType<string>());

				const string& retStr = any_cast<string>(retVal.get());
				EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(false));
			}
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(StaticMethodTest, overload_method_args_string_size_t_call)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_getProfile);
			ASSERT_TRUE(methOpt.has_value());

			const Method& getProfile = methOpt.value();
			const bool& signValid = getProfile.hasSignature<string, size_t>();
			ASSERT_TRUE(signValid);

			size_t age = person::AGE;
			string occupStr = person::OCCUPATION;

			const RStatus& callRet = getProfile()(occupStr, age);

			ASSERT_TRUE(callRet.didCallSucceed());

			const UniqueAny& retVal = callRet.releaseReturn();
			ASSERT_TRUE(retVal.get().has_value() && retVal.isOfType<string>());

			const string& retStr = any_cast<string>(retVal.get());
			const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

			EXPECT_EQ(retStr, checkStr);
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}
}