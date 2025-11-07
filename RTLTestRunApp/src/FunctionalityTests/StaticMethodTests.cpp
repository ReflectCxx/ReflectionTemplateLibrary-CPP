
#include <rtl/rtl.h>
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

		optional<Method> getDefaultsOpt = classPerson->getMethod(person::str_getDefaults);
		ASSERT_TRUE(getDefaultsOpt);
		EXPECT_TRUE(getDefaultsOpt->hasSignature<>());	//empty template params checks for zero arguments.
		{
			rtl::method<rtl::RObject, rtl::Return()> getDefaults = getDefaultsOpt.value().targetT().argsT().returnT();

			EXPECT_FALSE(getDefaults);
			EXPECT_EQ(getDefaults.get_init_error(), error::InvalidStaticMethodCaller);

			auto [err0, person] = classPerson->create<alloc::Heap>();

			EXPECT_EQ(err0, error::None);
			ASSERT_FALSE(person.isEmpty());

			auto [err, ret] = getDefaults(person)();

			EXPECT_EQ(err, error::InvalidStaticMethodCaller);
			EXPECT_TRUE(ret.isEmpty());
		} {
			rtl::static_method<rtl::Return()> getDefaults = getDefaultsOpt.value().argsT().returnT();

			auto [err, ret] = getDefaults();

			EXPECT_EQ(err, error::None);
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

		optional<Method> getProfileOpt = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfileOpt);
		EXPECT_TRUE((getProfileOpt->hasSignature<string, size_t>()));

		{
			rtl::method<rtl::RObject, rtl::Return(std::string, std::size_t)> getProfile = getProfileOpt.value()
																									   .targetT()
																									   .argsT<std::string, std::size_t>()
																									   .returnT();
			EXPECT_FALSE(getProfile);
			EXPECT_EQ(getProfile.get_init_error(), error::InvalidStaticMethodCaller);

			auto [err0, person] = classPerson->create<alloc::Heap>();

			EXPECT_EQ(err0, error::None);
			ASSERT_FALSE(person.isEmpty());

			auto [err, ret] = getProfile(person)(person::OCCUPATION, person::AGE);

			EXPECT_EQ(err, error::InvalidStaticMethodCaller);
			ASSERT_TRUE(ret.isEmpty());
		} {
			rtl::static_method<rtl::Return(std::string, std::size_t)> getProfile = getProfileOpt.value()
																							    .argsT<std::string, std::size_t>()
																							    .returnT();
			auto [err, ret] = getProfile(person::OCCUPATION, person::AGE);

			EXPECT_EQ(err, error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();
			EXPECT_EQ(retStr, checkStr);
		}
	}
}