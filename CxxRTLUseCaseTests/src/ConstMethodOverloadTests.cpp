#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(ConstMethodOverload, default_const_method_call__only_const_method_exists___on_heap_target)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			string firstName = person::FIRST_NAME;
			auto [err0, person] = classPerson.create<alloc::Heap>(firstName);

			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());
			ASSERT_TRUE(updateLastName->hasSignature<string>());

			string lastName = person::LAST_NAME;
			auto [err1, ret] = (*updateLastName)(person)(lastName);
			
			ASSERT_TRUE(err0 == error::None);
			ASSERT_TRUE(ret.isEmpty());
			EXPECT_TRUE(person::test_method_updateLastName_const(person.get(), person.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, default_const_method_call__only_const_method_exists__on_stack_target)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			string firstName = person::FIRST_NAME;
			auto [err0, person] = classPerson.create<alloc::Stack>(firstName);

			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());
			ASSERT_TRUE(updateLastName->hasSignature<string>());

			string lastName = person::LAST_NAME;
			auto [err1, ret] = (*updateLastName)(person)(lastName);

			ASSERT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());
			EXPECT_TRUE(person::test_method_updateLastName_const(person.get(), person.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, explicitly_const_method_call__only_const_method_exists__on_heap_target)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			string lastName = person::LAST_NAME;
			string firstName = person::FIRST_NAME;
			
			auto [err0, person] = classPerson.create<alloc::Heap>(firstName);

			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());
			ASSERT_TRUE(updateLastName->hasSignature<string>());
			{
				auto [err1, ret] = updateLastName->bind<methodQ::NonConst>(person).call(lastName);

				ASSERT_TRUE(err1 == error::NonConstMethodOverloadNotFound);
				ASSERT_TRUE(ret.isEmpty());
			} {
				auto [err1, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invalid argument

				ASSERT_TRUE(err1 == error::SignatureMismatch);
				ASSERT_TRUE(ret.isEmpty());
			} {
				auto [err1, ret] = updateLastName->bind<methodQ::Const>(person).call(lastName);

				ASSERT_TRUE(err1 == error::None);
				ASSERT_TRUE(ret.isEmpty());
			}
			EXPECT_TRUE(person::test_method_updateLastName_const(person.get(), person.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, explicitly_const_method_call__only_const_method_exists__on_stack_target)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classPerson = recOpt.value();
			optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
			ASSERT_TRUE(updateLastName);

			string lastName = person::LAST_NAME;
			string firstName = person::FIRST_NAME;

			auto [err0, person] = classPerson.create<alloc::Stack>(firstName);

			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());
			ASSERT_TRUE(updateLastName->hasSignature<string>());
			{
				auto [err1, ret] = updateLastName->bind<methodQ::NonConst>(person).call(lastName);

				ASSERT_TRUE(err1 == error::NonConstMethodOverloadNotFound);
				ASSERT_TRUE(ret.isEmpty());
			}
			{
				auto [err1, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invlid argument

				ASSERT_TRUE(err1 == error::SignatureMismatch);
				ASSERT_TRUE(ret.isEmpty());
			}
			{
				auto [err1, ret] = updateLastName->bind<methodQ::Const>(person).call(lastName);

				ASSERT_TRUE(err1 == error::None);
				ASSERT_TRUE(ret.isEmpty());
			}
			EXPECT_TRUE(person::test_method_updateLastName_const(person.get(), person.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, non_const_method_call__const_overload_exists__on_heap_target)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [err0, person] = classPerson->create<alloc::Heap>(firstName);

			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());
			ASSERT_TRUE(updateAddress->hasSignature<string>());
			{
				auto address = string(person::ADDRESS);
				auto [err, ret] = updateAddress->bind(person).call(address);

				ASSERT_TRUE(err == error::AmbiguousConstOverload);
				ASSERT_TRUE(ret.isEmpty());
			} {
				auto address = string(person::ADDRESS);
				auto [err, ret] = updateAddress->bind<methodQ::NonConst>(person).call(address);

				ASSERT_TRUE(err == error::None);
				ASSERT_TRUE(ret.isEmpty());
			}
			EXPECT_TRUE(person::test_method_updateAddress<string>(person.get(), person.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, non_const_method_call__const_overload_exists__on_stack_target)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());
			ASSERT_TRUE(updateAddress->hasSignature<string>());
			{
				auto address = string(person::ADDRESS);
				auto [err, ret] = updateAddress->bind(person).call(address);

				ASSERT_TRUE(err == error::AmbiguousConstOverload);
				ASSERT_TRUE(ret.isEmpty());
			} {
				auto address = string(person::ADDRESS);
				auto [err, ret] = updateAddress->bind<methodQ::NonConst>(person).call(address);

				ASSERT_TRUE(err == error::None);
				ASSERT_TRUE(ret.isEmpty());
			}
			EXPECT_TRUE(person::test_method_updateAddress<string>(person.get(), person.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_call__const_overload_exists__on_heap_target)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [err0, person] = classPerson->create<alloc::Heap>(firstName);

			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());
			ASSERT_TRUE(updateAddress->hasSignature<string>());
			{
				auto address = string(person::ADDRESS);
				auto [err, ret] = updateAddress->bind(person).call(address);

				ASSERT_TRUE(err == error::AmbiguousConstOverload);
				ASSERT_TRUE(ret.isEmpty());
			} {
				auto address = string(person::ADDRESS);
				auto [err, ret] = updateAddress->bind<methodQ::Const>(person).call(address);

				ASSERT_TRUE(err == error::None);
				ASSERT_TRUE(ret.isEmpty());
			}
			EXPECT_TRUE(person::test_method_updateAddress_const<string>(person.get(), person.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ConstMethodOverload, const_method_call__const_overload_exists__on_stack_target)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
			ASSERT_TRUE(updateAddress);

			string firstName = person::FIRST_NAME;
			auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());
			ASSERT_TRUE(updateAddress->hasSignature<string>());
			{
				auto address = string(person::ADDRESS);
				auto [err, ret] = updateAddress->bind(person).call(address);

				ASSERT_TRUE(err == error::AmbiguousConstOverload);
				ASSERT_TRUE(ret.isEmpty());
			} {
				auto address = string(person::ADDRESS);
				auto [err, ret] = updateAddress->bind<methodQ::Const>(person).call(address);

				ASSERT_TRUE(err == error::None);
				ASSERT_TRUE(ret.isEmpty());
			}
			EXPECT_TRUE(person::test_method_updateAddress_const<string>(person.get(), person.isOnHeap()));
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	//TEST(ConstMethodOverload, default_calling_of_const_method__no_const_overload__on_stack_target)
	//{
	//}


	//TEST(ConstMethodOverload, explicitly_calling_const_method__no_const_overload__on_heap_target)
	//{
	//}


	//TEST(ConstMethodOverload, explicitly_calling_const_method__no_const_overload__on_stack_target)
	//{

	//}

	//TEST(ConstMethodOverload, const_method_no_overload__call_on_const_target_on_heap_returns_string)
	//{
	//	{
	//		CxxMirror& cxxMirror = MyReflection::instance();

	//		optional<Record> recOpt = cxxMirror.getRecord(person::class_);
	//		ASSERT_TRUE(recOpt.has_value());

	//		const Record& classPerson = recOpt.value();
	//		optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
	//		ASSERT_TRUE(updateLastName);

	//		std::string firstName = person::FIRST_NAME;
	//		auto [err0, person] = classPerson.create<alloc::Heap>(firstName);

	//		ASSERT_TRUE(err0 == error::None);
	//		ASSERT_FALSE(person.isEmpty());

	//		optional<Method> getFirstName = classPerson.getMethod(person::str_getFirstName);
	//		ASSERT_TRUE(getFirstName);

	//		auto [err1, ret] = getFirstName->bind(person).call();
	//		ASSERT_TRUE(err1 == error::None);
	//		ASSERT_FALSE(ret.isEmpty());
	//		ASSERT_TRUE(ret.canViewAs<std::string>());

	//		const std::string& retStr = ret.view<std::string>()->get();
	//		ASSERT_EQ(retStr, firstName);
	//	}
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//	EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	//}


	//TEST(ConstMethodOverload, const_method_no_overload__call_on_const_target_on_stack_returns_string)
	//{
	//	{
	//		CxxMirror& cxxMirror = MyReflection::instance();

	//		optional<Record> recOpt = cxxMirror.getRecord(person::class_);
	//		ASSERT_TRUE(recOpt.has_value());

	//		const Record& classPerson = recOpt.value();
	//		optional<Method> updateLastName = classPerson.getMethod(person::str_updateLastName);
	//		ASSERT_TRUE(updateLastName);

	//		std::string firstName = person::FIRST_NAME;
	//		auto [err0, person] = classPerson.create<alloc::Stack>(firstName);

	//		ASSERT_TRUE(err0 == error::None);
	//		ASSERT_FALSE(person.isEmpty());

	//		optional<Method> getFirstName = classPerson.getMethod(person::str_getFirstName);
	//		ASSERT_TRUE(getFirstName);

	//		auto [err1, ret] = getFirstName->bind(person).call();
	//		ASSERT_TRUE(err1 == error::None);
	//		ASSERT_FALSE(ret.isEmpty());
	//		ASSERT_TRUE(ret.canViewAs<std::string>());

	//		const std::string& retStr = ret.view<std::string>()->get();
	//		ASSERT_EQ(retStr, firstName);
	//	}
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//	EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	//}


//	TEST(ConstMethodOverload, const_method_string_call_on_const_target_on_heap)
//	{
//		{
//			CxxMirror& cxxMirror = MyReflection::instance();
//
//			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
//			ASSERT_TRUE(classPerson);
//
//			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
//			ASSERT_TRUE(updateAddress);
//
//			string firstName = person::FIRST_NAME;
//			auto [status, personObj] = classPerson->create<alloc::Heap>(firstName);
//
//			ASSERT_TRUE(status);
//			ASSERT_FALSE(personObj.isEmpty());
//
//			personObj.makeConst();
//			ASSERT_TRUE(personObj.isConst());
//			ASSERT_TRUE(updateAddress->hasSignature<string>());
//
//			auto address = string(person::ADDRESS);
//			status = (*updateAddress)(personObj)(address);
//
//			ASSERT_TRUE(status);
//			EXPECT_TRUE(person::test_method_updateAddress_const<string>(personObj.get(), personObj.isOnHeap()));
//		}
//		EXPECT_TRUE(person::assert_zero_instance_count());
//		EXPECT_TRUE(Instance::getInstanceCount() == 0);
//	}
//
//
//	TEST(ConstMethodOverload, const_method_string_call_on_const_target_on_stack)
//	{
//		{
//			CxxMirror& cxxMirror = MyReflection::instance();
//
//			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
//			ASSERT_TRUE(classPerson);
//
//			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
//			ASSERT_TRUE(updateAddress);
//
//			string firstName = person::FIRST_NAME;
//			auto [status, personObj] = classPerson->create<alloc::Stack>(firstName);
//
//			ASSERT_TRUE(status);
//			ASSERT_FALSE(personObj.isEmpty());
//
//			personObj.makeConst();
//			ASSERT_TRUE(personObj.isConst());
//			ASSERT_TRUE(updateAddress->hasSignature<string>());
//
//			auto address = string(person::ADDRESS);
//			status = (*updateAddress)(personObj)(address);
//
//			ASSERT_TRUE(status);
//			EXPECT_TRUE(person::test_method_updateAddress_const<string>(personObj.get(), personObj.isOnHeap()));
//		}
//		EXPECT_TRUE(person::assert_zero_instance_count());
//		EXPECT_TRUE(Instance::getInstanceCount() == 0);
//	}
//
//
//	TEST(ConstMethodOverload, const_method_string_call_on_non_const_target_on_heap)
//	{
//		{
//			CxxMirror& cxxMirror = MyReflection::instance();
//
//			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
//			ASSERT_TRUE(classPerson);
//
//			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
//			ASSERT_TRUE(updateAddress);
//
//			string firstName = person::FIRST_NAME;
//			auto [status, personObj] = classPerson->create<alloc::Heap>(firstName);
//
//			ASSERT_TRUE(status);
//			ASSERT_FALSE(personObj.isEmpty());
//			ASSERT_FALSE(personObj.isConst());
//			ASSERT_TRUE(updateAddress->hasSignature<string>());
//
//			string address = person::ADDRESS;
//			status = (*updateAddress)(personObj)(address);
//
//			ASSERT_TRUE(status);
//			EXPECT_TRUE(person::test_method_updateAddress<string>(personObj.get(), personObj.isOnHeap()));
//		}
//		EXPECT_TRUE(person::assert_zero_instance_count());
//		EXPECT_TRUE(Instance::getInstanceCount() == 0);
//	}
//
//
//	TEST(ConstMethodOverload, const_method_string_call_on_non_const_target_on_stack)
//	{
//		{
//			CxxMirror& cxxMirror = MyReflection::instance();
//
//			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
//			ASSERT_TRUE(classPerson);
//
//			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
//			ASSERT_TRUE(updateAddress);
//
//			string firstName = person::FIRST_NAME;
//			auto [status, personObj] = classPerson->create<alloc::Stack>(firstName);
//
//			ASSERT_TRUE(status);
//			ASSERT_FALSE(personObj.isEmpty());
//			ASSERT_FALSE(personObj.isConst());
//			ASSERT_TRUE(updateAddress->hasSignature<string>());
//
//			string address = person::ADDRESS;
//			status = (*updateAddress)(personObj)(address);
//
//			ASSERT_TRUE(status);
//			EXPECT_TRUE(person::test_method_updateAddress<string>(personObj.get(), personObj.isOnHeap()));
//		}
//		EXPECT_TRUE(person::assert_zero_instance_count());
//		EXPECT_TRUE(Instance::getInstanceCount() == 0);
//	}
//
//
//	TEST(ConstMethodOverload, const_method_no_args_call_on_const_target_on_heap)
//	{
//		{
//			CxxMirror& cxxMirror = MyReflection::instance();
//
//			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
//			ASSERT_TRUE(recOpt.has_value());
//
//			const Record& classPerson = recOpt.value();
//			optional<Method> updateAddress = classPerson.getMethod(person::str_updateAddress);
//			ASSERT_TRUE(updateAddress);
//
//			string firstName = person::FIRST_NAME;
//			auto [status, personObj] = classPerson.create<alloc::Heap>(firstName);
//
//			ASSERT_TRUE(status);
//			ASSERT_FALSE(personObj.isEmpty());
//			ASSERT_FALSE(personObj.isConst());
//
//			personObj.makeConst();
//			ASSERT_TRUE(personObj.isConst());
//			ASSERT_TRUE(updateAddress->hasSignature<string>());
//
//			status = (*updateAddress)(personObj)();
//
//			ASSERT_TRUE(status);
//			EXPECT_TRUE(person::test_method_updateAddress_const(personObj.get(), personObj.isOnHeap()));
//		}
//		EXPECT_TRUE(person::assert_zero_instance_count());
//		EXPECT_TRUE(Instance::getInstanceCount() == 0);
//	}
//
//
//	TEST(ConstMethodOverload, const_method_no_args_call_on_const_target_on_stack)
//	{
//		{
//			CxxMirror& cxxMirror = MyReflection::instance();
//
//			optional<Record> recOpt = cxxMirror.getRecord(person::class_);
//			ASSERT_TRUE(recOpt.has_value());
//
//			const Record& classPerson = recOpt.value();
//			optional<Method> updateAddress = classPerson.getMethod(person::str_updateAddress);
//			ASSERT_TRUE(updateAddress);
//
//			string firstName = person::FIRST_NAME;
//			auto [status, personObj] = classPerson.create<alloc::Stack>(firstName);
//
//			ASSERT_TRUE(status);
//			ASSERT_FALSE(personObj.isEmpty());
//			ASSERT_FALSE(personObj.isConst());
//
//			personObj.makeConst();
//			ASSERT_TRUE(personObj.isConst());
//			ASSERT_TRUE(updateAddress->hasSignature<string>());
//
//			status = (*updateAddress)(personObj)();
//
//			ASSERT_TRUE(status);
//			EXPECT_TRUE(person::test_method_updateAddress_const(personObj.get(), personObj.isOnHeap()));
//		}
//		EXPECT_TRUE(person::assert_zero_instance_count());
//		EXPECT_TRUE(Instance::getInstanceCount() == 0);
//	}
//
//
//	TEST(ConstMethodOverload, const_method_no_args_call_on_non_const_target_on_heap)
//	{
//		{
//			CxxMirror& cxxMirror = MyReflection::instance();
//
//			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
//			ASSERT_TRUE(classPerson);
//
//			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
//			ASSERT_TRUE(updateAddress);
//
//			string firstName = person::FIRST_NAME;
//			auto [status, personObj] = classPerson->create<alloc::Heap>(firstName);
//
//			ASSERT_TRUE(status);
//			ASSERT_FALSE(personObj.isEmpty());
//			ASSERT_FALSE(personObj.isConst());
//			ASSERT_TRUE(updateAddress->hasSignature<string>());
//
//			status = (*updateAddress)(personObj)();
//
//			ASSERT_TRUE(status);
//			EXPECT_TRUE(person::test_method_updateAddress(personObj.get(), personObj.isOnHeap()));
//		}
//		EXPECT_TRUE(person::assert_zero_instance_count());
//		EXPECT_TRUE(Instance::getInstanceCount() == 0);
//	}
//
//
//	TEST(ConstMethodOverload, const_method_no_args_call_on_non_const_target_on_stack)
//	{
//		{
//			CxxMirror& cxxMirror = MyReflection::instance();
//
//			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
//			ASSERT_TRUE(classPerson);
//
//			optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
//			ASSERT_TRUE(updateAddress);
//
//			string firstName = person::FIRST_NAME;
//			auto [status, personObj] = classPerson->create<alloc::Stack>(firstName);
//
//			ASSERT_TRUE(status);
//			ASSERT_FALSE(personObj.isEmpty());
//			ASSERT_FALSE(personObj.isConst());
//			ASSERT_TRUE(updateAddress->hasSignature<string>());
//
//			status = (*updateAddress)(personObj)();
//
//			ASSERT_TRUE(status);
//			EXPECT_TRUE(person::test_method_updateAddress(personObj.get(), personObj.isOnHeap()));
//		}
//		EXPECT_TRUE(person::assert_zero_instance_count());
//		EXPECT_TRUE(Instance::getInstanceCount() == 0);
//	}
}