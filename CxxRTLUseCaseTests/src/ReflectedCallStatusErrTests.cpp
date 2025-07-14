
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests
{
	TEST(ReflectedCallStatusError, construct_on_heap___error_ConstructorNotRegisteredInRTL)
	{
		optional<Record> classLibrary = MyReflection::instance().getRecord(library::class_);
		ASSERT_TRUE(classLibrary);

		auto [status, instance] = classLibrary->create<alloc::Heap>();

		ASSERT_TRUE(status == error::ConstructorNotRegisteredInRTL);
		ASSERT_TRUE(instance.isEmpty());
	}


	TEST(ReflectedCallStatusError, construct_on_stack___error_ConstructorNotRegisteredInRTL)
	{
		optional<Record> classLibrary = MyReflection::instance().getRecord(library::class_);
		ASSERT_TRUE(classLibrary);

		auto [status, instance] = classLibrary->create<alloc::Stack>();

		ASSERT_TRUE(status == error::ConstructorNotRegisteredInRTL);
		ASSERT_TRUE(instance.isEmpty());
	}


	TEST(ReflectedCallStatusError, copy_construct_on_heap___error_CopyConstructorPrivateOrDeleted)
	{
		{
			optional<Record> classCalender = MyReflection::instance().getRecord(calender::ns, calender::struct_);
			ASSERT_TRUE(classCalender);

			auto [err0, srcObj] = classCalender->create<alloc::Heap>();
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(srcObj.isEmpty());

			auto [err1, copyObj] = classCalender->clone(srcObj);

			// Cannot create heap instance: Calender's copy constructor is deleted.
			ASSERT_TRUE(err1 == error::CopyConstructorPrivateOrDeleted);
			ASSERT_TRUE(copyObj.isEmpty());
		}
		EXPECT_TRUE(calender::assert_zero_instance_count());
	}


	TEST(ReflectedCallStatusError, copy_construct_on_stack___error_CopyConstructorPrivateOrDeleted)
	{
		{
			optional<Record> classCalender = MyReflection::instance().getRecord(calender::ns, calender::struct_);
			ASSERT_TRUE(classCalender);

			auto [err, robj] = classCalender->create<alloc::Stack>();

			// Cannot create stack instance: Calender's copy constructor is deleted, but std::any requires copy-constructible type
			ASSERT_TRUE(err == error::CopyConstructorPrivateOrDeleted);
			ASSERT_TRUE(robj.isEmpty());
		}
		EXPECT_TRUE(calender::assert_zero_instance_count());
	}


	TEST(ReflectedCallStatusError, static_method_call_wrong_args___error_SignatureMismatch)
	{
		optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfile);
		ASSERT_TRUE(getProfile->hasSignature<>());  //empty template params checks for zero arguments.

		auto [err, robj] = getProfile->bind().call(std::string());

		ASSERT_TRUE(err == error::SignatureMismatch);
		ASSERT_TRUE(robj.isEmpty());
	}


	TEST(ReflectedCallStatusError, copy_ctor_on_empty_instance___error_EmptyRObject)
	{
		{
			RObject emptyObj;
			ASSERT_TRUE(emptyObj.isEmpty());

			optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			auto [err, person] = classPerson->clone(emptyObj);

			ASSERT_TRUE(err == error::EmptyRObject);
			ASSERT_TRUE(person.isEmpty());
		}
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ReflectedCallStatusError, method_call_on_empty_instance___error_EmptyObject)
	{
		{
			RObject emptyObj;
			ASSERT_TRUE(emptyObj.isEmpty());

			optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err, ret] = classBook->getMethod(book::str_getPublishedOn)->bind(emptyObj).call();
			ASSERT_TRUE(err == error::EmptyRObject);
			ASSERT_TRUE(ret.isEmpty());
		}
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ReflectedCallStatusError, method_on_wrong_heap_instance___error_ReflectedObjectTypeMismatch)
	{
		{
			optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err0, person] = classPerson->create<alloc::Heap>();
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			auto [err1, ret] = getPublishedOn->bind(person).call();
			ASSERT_TRUE(err1 == error::ReflectedObjectTypeMismatch);
			ASSERT_TRUE(ret.isEmpty());
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(ReflectedCallStatusError, method_on_wrong_stack_instance___error_ReflectedObjectTypeMismatch)
	{
		{
			optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err0, person] = classPerson->create<alloc::Stack>();
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			auto [err1, ret] = getPublishedOn->bind(person).call();
			ASSERT_TRUE(err1 == error::ReflectedObjectTypeMismatch);
			ASSERT_TRUE(ret.isEmpty());
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	//TEST(ReflectedCallStatusError, non_const_method_on_const_Instance_on_heap___error_InstanceConstMismatch)
	//{
	//	{	
	//		optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
	//		ASSERT_TRUE(classBook);

	//		auto [status, bookObj] = classBook->create<alloc::Heap>();
	//		ASSERT_TRUE(status);
	//		ASSERT_FALSE(bookObj.isEmpty());

	//		optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
	//		ASSERT_TRUE(getPublishedOn);

	//		bookObj.makeConst();
	//		status = getPublishedOn->bind(bookObj).call();

	//		ASSERT_TRUE(status == error::InstanceConstMismatch);
	//	}
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//	EXPECT_TRUE(Instance::getInstanceCount() == 0);
	//}


	//TEST(ReflectedCallStatusError, non_const_method_on_const_Instance_on_stack___error_InstanceConstMismatch)
	//{
	//	{
	//		optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
	//		ASSERT_TRUE(classBook);

	//		auto [status, bookObj] = classBook->create<alloc::Stack>();
	//		ASSERT_TRUE(status);
	//		ASSERT_FALSE(bookObj.isEmpty());

	//		optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
	//		ASSERT_TRUE(getPublishedOn);

	//		bookObj.makeConst();
	//		status = getPublishedOn->bind(bookObj).call();

	//		ASSERT_TRUE(status == error::InstanceConstMismatch);
	//	}
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//	EXPECT_TRUE(Instance::getInstanceCount() == 0);
	//}
}