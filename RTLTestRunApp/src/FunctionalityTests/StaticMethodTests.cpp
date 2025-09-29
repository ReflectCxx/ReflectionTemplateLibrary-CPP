
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl;

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
	TEST(StaticMethods, unique_method_call)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getDefaults = classPerson->getMethod(person::str_getDefaults);
		ASSERT_TRUE(getDefaults);
		EXPECT_TRUE(getDefaults->hasSignature<>());	//empty template params checks for zero arguments.

		auto [err, ret] = getDefaults->bind().call();
		EXPECT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		EXPECT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
		EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
	}


	TEST(StaticMethods, overload_method_void_call)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfile);
		EXPECT_TRUE(getProfile->hasSignature<>());	//empty template params checks for zero arguments.

		auto [err, ret] = getProfile->bind().call();
		EXPECT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		EXPECT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
		EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile());
	}


	TEST(StaticMethods, overload_method_args_bool_call)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfile);
		EXPECT_TRUE(getProfile->hasSignature<bool>());
		{
			auto [err, ret] = getProfile->bind().call(true);
			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(true));
		} {
			//use the bind-call syntax.
			auto [err, ret] = getProfile->bind().call(false);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(false));
		}
	}


	TEST(StaticMethods, overload_method_args_string_size_t_call)
	{
		optional<Record> recOpt = cxx::mirror().getRecord(person::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classPerson = recOpt.value();
		optional<Method> methOpt = classPerson.getMethod(person::str_getProfile);
		ASSERT_TRUE(methOpt.has_value());

		const Method& getProfile = methOpt.value();
		EXPECT_TRUE((getProfile.hasSignature<string, size_t>()));

		size_t age = person::AGE;
		string occupation = person::OCCUPATION;
		auto [err, ret] = getProfile.bind().call(occupation, age);

		EXPECT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		EXPECT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
		const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

		EXPECT_EQ(retStr, checkStr);
	}


	TEST(StaticMethods, static_method_call_on_target_instance)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getDefaults = classPerson->getMethod(person::str_getDefaults);
		ASSERT_TRUE(getDefaults);
		EXPECT_TRUE(getDefaults->hasSignature<>());	//empty template params checks for zero arguments.

		auto [err0, person] = classPerson->create<alloc::Heap>();

		EXPECT_TRUE(err0 == error::None);
		ASSERT_FALSE(person.isEmpty());
		{
			auto [err, ret] = (*getDefaults)(person)();
			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			auto& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
		} {
			auto [err, ret] = getDefaults->bind(person).call();
			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			auto& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
		}
	}


	TEST(StaticMethods, static_method_call_on_target_instance_with_args)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		auto [err0, person] = classPerson->create<alloc::Heap>();

		EXPECT_TRUE(err0 == error::None);
		ASSERT_FALSE(person.isEmpty());

		optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfile);
		EXPECT_TRUE((getProfile->hasSignature<string, size_t>()));

		size_t age = person::AGE;
		string occupation = person::OCCUPATION;
		{
			auto [err, ret] = getProfile->bind(person).call(occupation, age);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

			EXPECT_EQ(retStr, checkStr);
		} {
			auto [err, ret] = (*getProfile)(person)(occupation, age);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

			EXPECT_EQ(retStr, checkStr);
		}
	}
}