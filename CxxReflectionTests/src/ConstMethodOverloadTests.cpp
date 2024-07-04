#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	//TEST(ConstMethodOverloadTest, const_method_no_overload_call_on_non_const_target)
	//{
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//	{
	//		CxxMirror& cxxMirror = MyReflection::instance();

	//		optional<Record> recOpt = cxxMirror.getRecord(person::class_);
	//		ASSERT_TRUE(recOpt.has_value());

	//		const Record& classPerson = recOpt.value();
	//		optional<Method> methOpt = classPerson.getMethod(person::str_updateLastName);
	//		ASSERT_TRUE(methOpt.has_value());

	//		const RStatus& retIns = classPerson.instance(string(person::FIRST_NAME));
	//		ASSERT_TRUE(retIns.didCallSucceed());

	//		UniqueAny personObj = retIns.releaseReturn();
	//		ASSERT_TRUE(personObj.get().has_value());

	//		const Method& updateLastName = methOpt.value();
	//		const RStatus& callRet = updateLastName(personObj).invoke(string(person::LAST_NAME));
	//		
	//		ASSERT_TRUE(callRet.didCallSucceed());
	//		EXPECT_TRUE(person::test_method_updateLastName(personObj.get()));
	//	}
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//}


	//TEST(ConstMethodOverloadTest, const_method_no_overload_call_on_const_target)
	//{
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//	{
	//		CxxMirror& cxxMirror = MyReflection::instance();

	//		optional<Record> recOpt = cxxMirror.getRecord(person::class_);
	//		ASSERT_TRUE(recOpt.has_value());

	//		const Record& classPerson = recOpt.value();
	//		optional<Method> methOpt = classPerson.getMethod(person::str_updateLastName);
	//		ASSERT_TRUE(methOpt.has_value());

	//		const RStatus& retIns = classPerson.instance(string(person::FIRST_NAME));
	//		ASSERT_TRUE(retIns.didCallSucceed());

	//		UniqueAny personObj = retIns.releaseReturn();
	//		ASSERT_TRUE(personObj.get().has_value());

	//		personObj.makeConst();
	//		auto cv = personObj.getQualifier();

	//		//ASSERT_TRUE(personObj.getQualifier() == TypeQ::Const);

	//		const Method& updateLastName = methOpt.value();
	//		const RStatus& callRet = updateLastName(personObj).invoke(string(person::LAST_NAME));

	//		ASSERT_TRUE(callRet.didCallSucceed());
	//		EXPECT_TRUE(person::test_method_updateLastName_const(personObj.get()));
	//	}
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//}
}