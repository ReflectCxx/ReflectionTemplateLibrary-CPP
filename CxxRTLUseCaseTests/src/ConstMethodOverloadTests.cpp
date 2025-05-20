#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(ConstMethodOverload, const_method_no_overload_call_on_non_const_target_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance<alloc::Heap>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateLastName->hasSignature<string>());

			string lastName = person::LAST_NAME;
			status = (*updateLastName)(personObj)(lastName);
			
			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateLastName(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_overload_call_on_non_const_target_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance<alloc::Stack>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateLastName->hasSignature<string>());

			string lastName = person::LAST_NAME;
			status = (*updateLastName)(personObj)(lastName);

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateLastName(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_overload_call_on_const_target_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance<alloc::Heap>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateLastName->hasSignature<string>());

			string lastName = person::LAST_NAME;
			status = (*updateLastName)(personObj)(lastName);

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateLastName_const(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_overload_call_on_const_target_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance<alloc::Stack>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateLastName->hasSignature<string>());

			string lastName = person::LAST_NAME;
			status = (*updateLastName)(personObj)(lastName);

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateLastName_const(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_overload_call_on_const_target_on_heap_returns_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			std::string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance<alloc::Heap>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());

			optional<Method> getFirstName = classPerson.getMethod(person::str_getFirstName);
			ASSERT_TRUE(getFirstName);

			status = getFirstName->bind(personObj).call();
			ASSERT_TRUE(status);
			ASSERT_TRUE(status.isOfType<std::string>());

			const std::string retStr = std::any_cast<std::string>(status.getReturn());
			ASSERT_EQ(retStr, firstName);
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_overload_call_on_const_target_on_stack_returns_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			std::string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance<alloc::Stack>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());

			optional<Method> getFirstName = classPerson.getMethod(person::str_getFirstName);
			ASSERT_TRUE(getFirstName);

			status = getFirstName->bind(personObj).call();
			ASSERT_TRUE(status);
			ASSERT_TRUE(status.isOfType<std::string>());

			const std::string retStr = std::any_cast<std::string>(status.getReturn());
			ASSERT_EQ(retStr, firstName);
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_string_call_on_const_target_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson->instance<alloc::Heap>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			auto address = string(person::ADDRESS);
			status = (*updateAddress)(personObj)(address);

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateAddress_const<string>(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_string_call_on_const_target_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson->instance<alloc::Stack>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			auto address = string(person::ADDRESS);
			status = (*updateAddress)(personObj)(address);

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateAddress_const<string>(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_string_call_on_non_const_target_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson->instance<alloc::Heap>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			string address = person::ADDRESS;
			status = (*updateAddress)(personObj)(address);

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateAddress<string>(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_string_call_on_non_const_target_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson->instance<alloc::Stack>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			string address = person::ADDRESS;
			status = (*updateAddress)(personObj)(address);

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateAddress<string>(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_args_call_on_const_target_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateAddress = classPerson.getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance<alloc::Heap>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			status = (*updateAddress)(personObj)();

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateAddress_const(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_args_call_on_const_target_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateAddress = classPerson.getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson.instance<alloc::Stack>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());

			personObj.makeConst();
			ASSERT_TRUE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			status = (*updateAddress)(personObj)();

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateAddress_const(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_args_call_on_non_const_target_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson->instance<alloc::Heap>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			status = (*updateAddress)(personObj)();

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateAddress(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_no_args_call_on_non_const_target_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [status, personObj] = classPerson->instance<alloc::Stack>(firstName);

			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());
			ASSERT_FALSE(personObj.isConst());
			ASSERT_TRUE(updateAddress->hasSignature<string>());

			status = (*updateAddress)(personObj)();

			ASSERT_TRUE(status);
			EXPECT_TRUE(person::test_method_updateAddress(personObj.get(), personObj.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}
}