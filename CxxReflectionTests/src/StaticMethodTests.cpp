
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(StaticMethods, unique_method_call)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> classPerson = cxxMirror.getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getDefaults = classPerson->getMethod(person::str_getDefaults);
		ASSERT_TRUE(getDefaults);
		ASSERT_TRUE(getDefaults->hasSignature<void>());

		const RStatus& status = (*getDefaults)()();
		ASSERT_TRUE(status);
		ASSERT_TRUE(status.getReturn().has_value());
		ASSERT_TRUE(status.isOfType<string>());

		const string& retStr = any_cast<string>(status.getReturn());
		EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
	}


	TEST(StaticMethods, overload_method_void_call)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> classPerson = cxxMirror.getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfile);
		ASSERT_TRUE(getProfile->hasSignature<void>());

		const RStatus& status = (*getProfile)()();
		ASSERT_TRUE(status);
		ASSERT_TRUE(status.getReturn().has_value());
		ASSERT_TRUE(status.isOfType<string>());

		const string& retStr = any_cast<string>(status.getReturn());
		EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile());
	}


	TEST(StaticMethods, overload_method_args_bool_call)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> classPerson = cxxMirror.getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfile);
		ASSERT_TRUE(getProfile->hasSignature<bool>());
		{
			const RStatus& status = (*getProfile)()(true);
			ASSERT_TRUE(status);
			ASSERT_TRUE(status.getReturn().has_value());
			ASSERT_TRUE(status.isOfType<string>());

			const string& retStr = any_cast<string>(status.getReturn());
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(true));
		}
		{
			const RStatus& status = (*getProfile)()(false);
			ASSERT_TRUE(status);
			ASSERT_TRUE(status.getReturn().has_value());
			ASSERT_TRUE(status.isOfType<string>());

			const string& retStr = any_cast<string>(status.getReturn());
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(false));
		}
	}


	TEST(StaticMethods, overload_method_args_string_size_t_call)
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

		const RStatus& status = getProfile()(string(person::OCCUPATION), person::AGE);

		ASSERT_TRUE(status);
		ASSERT_TRUE(status.getReturn().has_value());
		ASSERT_TRUE(status.isOfType<string>());

		const string& retStr = any_cast<string>(status.getReturn());
		const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

		EXPECT_EQ(retStr, checkStr);
	}
}