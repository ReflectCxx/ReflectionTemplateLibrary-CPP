#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(ConstMethodOverloadTest, const_method_no_overload_call_on_non_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(methOpt.has_value());

			auto [status, personObj] = classPerson.instance(string(person::FIRST_NAME));
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			const Method& updateLastName = methOpt.value();
			ASSERT_TRUE(updateLastName.hasSignature<string>());

			string lnameStr = person::LAST_NAME;
			const RStatus& retObj = updateLastName(personObj)(lnameStr);
			
			ASSERT_TRUE(retObj.didCallSucceed());
			EXPECT_TRUE(person::test_method_updateLastName(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverloadTest, const_method_no_overload_call_on_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(methOpt.has_value());

			string fnameStr = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance(fnameStr);
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());

			const Method& updateLastName = methOpt.value();
			ASSERT_TRUE(updateLastName.hasSignature<string>());

			string lnameStr = person::LAST_NAME;
			const RStatus& retObj = updateLastName(personObj)(lnameStr);

			ASSERT_TRUE(retObj.didCallSucceed());
			EXPECT_TRUE(person::test_method_updateLastName_const(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverloadTest, const_method_string_call_on_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_updateAddress);
			ASSERT_TRUE(methOpt.has_value());

			string fnameStr = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance(fnameStr);
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());

			const Method& updateAddress = methOpt.value();
			ASSERT_TRUE(updateAddress.hasSignature<string>());

			string address = person::ADDRESS;
			const RStatus& retObj = updateAddress(personObj)(address);

			ASSERT_TRUE(retObj.didCallSucceed());
			EXPECT_TRUE(person::test_method_updateAddress_const<string>(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverloadTest, const_method_string_call_on_non_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_updateAddress);
			ASSERT_TRUE(methOpt.has_value());

			string fnameStr = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance(fnameStr);
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			const Method& updateAddress = methOpt.value();
			ASSERT_TRUE(updateAddress.hasSignature<string>());

			string address = person::ADDRESS;
			const RStatus& retObj = updateAddress(personObj)(address);

			ASSERT_TRUE(retObj.didCallSucceed());
			EXPECT_TRUE(person::test_method_updateAddress<string>(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverloadTest, const_method_no_args_call_on_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_updateAddress);
			ASSERT_TRUE(methOpt.has_value());

			string fnameStr = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance(fnameStr);
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());

			const Method& updateAddress = methOpt.value();
			ASSERT_TRUE(updateAddress.hasSignature<string>());

			const RStatus& retObj = updateAddress(personObj)();

			ASSERT_TRUE(retObj.didCallSucceed());
			EXPECT_TRUE(person::test_method_updateAddress_const(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverloadTest, const_method_no_args_call_on_non_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> methOpt = classPerson.getMethod(person::str_updateAddress);
			ASSERT_TRUE(methOpt.has_value());

			string fnameStr = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance(fnameStr);
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			const Method& updateAddress = methOpt.value();
			ASSERT_TRUE(updateAddress.hasSignature<string>());

			const RStatus& retObj = updateAddress(personObj)();

			ASSERT_TRUE(retObj.didCallSucceed());
			EXPECT_TRUE(person::test_method_updateAddress(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}
}