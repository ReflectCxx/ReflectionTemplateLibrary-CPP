
#include <rtl_access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl;

using namespace test_utils;


namespace rtl_tests
{
	TEST(StaticMethods, unique_method_call)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(cxx::type::Person::id);
		ASSERT_TRUE(classPerson);

		optional<Method> optGetDefaults = classPerson->getMethod(cxx::type::Person::fn::getDefaults::id);
		ASSERT_TRUE(optGetDefaults);
		EXPECT_TRUE(optGetDefaults->hasSignature<>());	//empty template params checks for zero arguments.

		auto getDefaultsFn = optGetDefaults->argsT<>().returnT<>();
		ASSERT_TRUE(getDefaultsFn);
		EXPECT_EQ(getDefaultsFn.get_init_error(), rtl::error::None);

		auto [err, ret] = getDefaultsFn();
		EXPECT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		EXPECT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
		EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
	}


	TEST(StaticMethods, overload_method_void_call)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(cxx::type::Person::id);
		ASSERT_TRUE(classPerson);

		optional<Method> optGetProfile = classPerson->getMethod(cxx::type::Person::fn::getProfile::id);
		ASSERT_TRUE(optGetProfile);
		EXPECT_TRUE(optGetProfile->hasSignature<>());	//empty template params checks for zero arguments.

		auto getProfileFn = optGetProfile->argsT<>().returnT<>();
		ASSERT_TRUE(getProfileFn);
		EXPECT_EQ(getProfileFn.get_init_error(), rtl::error::None);

		auto [err, ret] = getProfileFn();
		EXPECT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		EXPECT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
		EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile());
	}


	TEST(StaticMethods, overload_method_args_bool_call)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(cxx::type::Person::id);
		ASSERT_TRUE(classPerson);

		optional<Method> optGetProfile = classPerson->getMethod(cxx::type::Person::fn::getProfile::id);
		ASSERT_TRUE(optGetProfile);
		EXPECT_TRUE(optGetProfile->hasSignature<bool>());

		auto getProfileFn = optGetProfile->argsT<bool>().returnT<>();
		ASSERT_TRUE(getProfileFn);
		EXPECT_EQ(getProfileFn.get_init_error(), rtl::error::None);
		{
			auto [err, ret] = getProfileFn(true);
			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(true));
		} {
			//use the bind-call syntax.
			auto [err, ret] = getProfileFn.bind<bool>()(false);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getProfile<bool>(false));
		}
	}


	TEST(StaticMethods, overload_method_args_string_size_t_call)
	{
		optional<Record> recOpt = cxx::mirror().getRecord(cxx::type::Person::id);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classPerson = recOpt.value();
		optional<Method> methOpt = classPerson.getMethod(cxx::type::Person::fn::getProfile::id);
		ASSERT_TRUE(methOpt.has_value());

		const Method& optGetProfile = methOpt.value();
		EXPECT_TRUE((optGetProfile.hasSignature<string, size_t>()));

		auto getProfileFn = optGetProfile.argsT<string, size_t>().returnT<>();
		ASSERT_TRUE(getProfileFn);
		EXPECT_EQ(getProfileFn.get_init_error(), rtl::error::None);

		auto [err, ret] = getProfileFn(person::OCCUPATION.data(), person::AGE);

		EXPECT_TRUE(err == error::None);
		ASSERT_FALSE(ret.isEmpty());
		EXPECT_TRUE(ret.canViewAs<string>());

		const string& retStr = ret.view<string>()->get();
		const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();

		EXPECT_EQ(retStr, checkStr);
	}


	TEST(StaticMethods, static_method_call_on_target_instance)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(cxx::type::Person::id);
		ASSERT_TRUE(classPerson);

		optional<Method> getDefaultsOpt = classPerson->getMethod(cxx::type::Person::fn::getDefaults::id);
		ASSERT_TRUE(getDefaultsOpt);
		EXPECT_TRUE(getDefaultsOpt->hasSignature<>());	//empty template params checks for zero arguments.
		{
			rtl::method<rtl::RObject, rtl::Return()> getDefaultsFn = getDefaultsOpt.value().targetT().argsT().returnT();

			EXPECT_FALSE(getDefaultsFn);
			EXPECT_EQ(getDefaultsFn.get_init_error(), error::SignatureMismatch);

			auto [err0, person] = classPerson->ctorT<>()(alloc::Heap);

			EXPECT_EQ(err0, error::None);
			ASSERT_FALSE(person.isEmpty());

			auto [err, ret] = getDefaultsFn(person)();

			EXPECT_EQ(err, error::SignatureMismatch);
			EXPECT_TRUE(ret.isEmpty());
		} {
			rtl::static_method<rtl::Return()> getDefaultsFn = getDefaultsOpt.value().argsT().returnT();

			auto [err, ret] = getDefaultsFn();

			EXPECT_EQ(err, error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			auto& retStr = ret.view<string>()->get();
			EXPECT_EQ(retStr, person::get_str_returned_on_call_getDefaults());
		}
	}


	TEST(StaticMethods, static_method_call_on_target_instance_with_args)
	{
		optional<Record> classPerson = cxx::mirror().getRecord(cxx::type::Person::id);
		ASSERT_TRUE(classPerson);

		optional<Method> getProfileOpt = classPerson->getMethod(cxx::type::Person::fn::getProfile::id);
		ASSERT_TRUE(getProfileOpt);
		EXPECT_TRUE((getProfileOpt->hasSignature<string, size_t>()));

		{
			rtl::method<rtl::RObject, rtl::Return(std::string, std::size_t)> optGetProfile = getProfileOpt.value()
																									   .targetT()
																									   .argsT<std::string, std::size_t>()
																									   .returnT();
			EXPECT_FALSE(optGetProfile);
			EXPECT_EQ(optGetProfile.get_init_error(), error::SignatureMismatch);

			auto [err0, person] = classPerson->ctorT()(alloc::Heap);

			EXPECT_EQ(err0, error::None);
			ASSERT_FALSE(person.isEmpty());

			auto [err, ret] = optGetProfile(person)(person::OCCUPATION.data(), person::AGE);

			EXPECT_EQ(err, error::SignatureMismatch);
			ASSERT_TRUE(ret.isEmpty());
		} {
			rtl::static_method<rtl::Return(std::string, std::size_t)> optGetProfile = getProfileOpt.value()
																							    .argsT<std::string, std::size_t>()
																							    .returnT();
			auto [err, ret] = optGetProfile(person::OCCUPATION.data(), person::AGE);

			EXPECT_EQ(err, error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const string& retStr = ret.view<string>()->get();
			const string& checkStr = person::get_str_returned_on_call_getProfile<string, size_t>();
			EXPECT_EQ(retStr, checkStr);
		}
	}
}