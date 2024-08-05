
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
		ASSERT_TRUE(getDefaults->hasSignature<>());	//empty template params checks for zero arguments.

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
		ASSERT_TRUE(getProfile->hasSignature<>());	//empty template params checks for zero arguments.

		const RStatus& status = getProfile->on().call();
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
		} {
			//different syntax of calling.
			const RStatus& status = getProfile->on().call(false);

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

		const RStatus& status = getProfile.on().call(string(person::OCCUPATION), person::AGE);

		ASSERT_TRUE(status);
		ASSERT_TRUE(status.getReturn().has_value());
		ASSERT_TRUE(status.isOfType<string>());

		const string& retStr = any_cast<string>(status.getReturn());
		const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

		EXPECT_EQ(retStr, checkStr);
	}


	TEST(StaticMethods, static_method_call_on_target_instance)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> classPerson = cxxMirror.getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getDefaults = classPerson->getMethod(person::str_getDefaults);
		ASSERT_TRUE(getDefaults);
		ASSERT_TRUE(getDefaults->hasSignature<>());	//empty template params checks for zero arguments.

		auto [isSuccess, personObj] = classPerson->instance();

		ASSERT_TRUE(isSuccess);
		ASSERT_FALSE(personObj.isEmpty());

		//TODO: handle this test case with appropriate error or make successful call as its valid to call static method on objects.
		const RStatus& status = (*getDefaults)(personObj)();
		ASSERT_TRUE(status == rtl::Error::InstanceTypeMismatch);
	}
}