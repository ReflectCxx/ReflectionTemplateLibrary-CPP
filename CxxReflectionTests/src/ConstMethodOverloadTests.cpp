#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(ConstMethodOverload, const_method_no_overload_call_on_non_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			auto [status, personObj] = classPerson.instance(string(person::FIRST_NAME));

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateLastName->hasSignature<string>());

			const RStatus& rStatus = (*updateLastName)(personObj)(string(person::LAST_NAME));
			
			ASSERT_TRUE(rStatus);
			EXPECT_TRUE(person::test_method_updateLastName(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverload, const_method_no_overload_call_on_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			auto [status, personObj] = classPerson.instance(string(person::FIRST_NAME));

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateLastName->hasSignature<string>());

			const RStatus& rStatus = (*updateLastName)(personObj)(string(person::LAST_NAME));

			ASSERT_TRUE(rStatus);
			EXPECT_TRUE(person::test_method_updateLastName_const(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverload, const_method_string_call_on_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string fnameStr = person::FIRST_NAME;
			auto [status, personObj] = classPerson->instance(fnameStr);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			const RStatus& rStatus = (*updateAddress)(personObj)(string(person::ADDRESS));

			ASSERT_TRUE(rStatus);
			EXPECT_TRUE(person::test_method_updateAddress_const<string>(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverload, const_method_string_call_on_non_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			auto [status, personObj] = classPerson->instance(string(person::FIRST_NAME));

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			const RStatus& rStatus = (*updateAddress)(personObj)(string(person::ADDRESS));

			ASSERT_TRUE(rStatus);
			EXPECT_TRUE(person::test_method_updateAddress<string>(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverload, const_method_no_args_call_on_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateAddress = classPerson.getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			auto [status, personObj] = classPerson.instance(string(person::FIRST_NAME));

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			const RStatus& rStatus = (*updateAddress)(personObj)();

			ASSERT_TRUE(rStatus);
			EXPECT_TRUE(person::test_method_updateAddress_const(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ConstMethodOverload, const_method_no_args_call_on_non_const_target)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string fnameStr = person::FIRST_NAME;
			auto [status, personObj] = classPerson->instance(fnameStr);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			const RStatus& rStatus = (*updateAddress)(personObj)();

			ASSERT_TRUE(rStatus);
			EXPECT_TRUE(person::test_method_updateAddress(personObj.get()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}
}