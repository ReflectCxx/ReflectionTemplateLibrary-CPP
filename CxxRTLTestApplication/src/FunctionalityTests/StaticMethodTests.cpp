
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl;
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

		auto [err, ret] = (*getDefaults)()();
		ASSERT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		ASSERT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
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

		auto [err, ret] = getProfile->bind().call();
		ASSERT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		ASSERT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
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
			auto [err, ret] = (*getProfile)()(true);
			ASSERT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(true));
		} {
			//use the bind-call syntax.
			auto [err, ret] = getProfile->bind().call(false);

			ASSERT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
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
		ASSERT_TRUE((getProfile.hasSignature<string, size_t>()));

		size_t age = person::AGE;
		string occupation = person::OCCUPATION;
		auto [err, ret] = getProfile.bind().call(occupation, age);

		ASSERT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		ASSERT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
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

		auto [err0, person] = classPerson->create<alloc::Heap>();

		ASSERT_TRUE(err0 == error::None);
		ASSERT_FALSE(person.isEmpty());
		{
			auto [err, ret] = (*getDefaults)(person)();
			ASSERT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			auto& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
		} {
			auto [err, ret] = getDefaults->bind(person).call();
			ASSERT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			auto& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
		}
	}


	TEST(StaticMethods, static_method_call_on_target_instance_with_args)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> classPerson = cxxMirror.getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		auto [err0, person] = classPerson->create<alloc::Heap>();

		ASSERT_TRUE(err0 == error::None);
		ASSERT_FALSE(person.isEmpty());

		optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfile);
		ASSERT_TRUE((getProfile->hasSignature<string, size_t>()));

		size_t age = person::AGE;
		string occupation = person::OCCUPATION;
		{
			auto [err, ret] = getProfile->bind(person).call(occupation, age);

			ASSERT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

			EXPECT_EQ(retStr, checkStr);
		} {
			auto [err, ret] = (*getProfile)(person)(occupation, age);

			ASSERT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			ASSERT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

			EXPECT_EQ(retStr, checkStr);
		}
	}
}