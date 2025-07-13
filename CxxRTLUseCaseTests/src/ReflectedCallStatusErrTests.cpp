
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
	TEST(ReflectedCallStatusError, construct_on_heap___error_ConstructorNotFound)
	{
		optional<Record> classLibrary = MyReflection::instance().getRecord(library::class_);
		ASSERT_TRUE(classLibrary);

		auto [status, instance] = classLibrary->create<alloc::Heap>();

		ASSERT_TRUE(status == error::ReflectedConstructorNotFound);
		ASSERT_TRUE(instance.isEmpty());
	}


	TEST(ReflectedCallStatusError, construct_on_stack___error_ConstructorNotFound)
	{
		optional<Record> classLibrary = MyReflection::instance().getRecord(library::class_);
		ASSERT_TRUE(classLibrary);

		auto [status, instance] = classLibrary->create<alloc::Stack>();

		ASSERT_TRUE(status == error::ReflectedConstructorNotFound);
		ASSERT_TRUE(instance.isEmpty());
	}


	TEST(ReflectedCallStatusError, copy_construct_on_heap___error_CopyConstructorDeleted)
	{
		{
			optional<Record> classCalender = MyReflection::instance().getRecord(calender::ns, calender::struct_);
			ASSERT_TRUE(classCalender);

			auto [err0, srcObj] = classCalender->create<alloc::Heap>();
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(srcObj.isEmpty());

			auto [err1, copyObj] = classCalender->clone(srcObj);
			ASSERT_TRUE(err1 == error::CopyConstructorDisabled);
			ASSERT_TRUE(copyObj.isEmpty());
		}
		EXPECT_TRUE(calender::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflecetedInstanceCount() == 0);
	}


	//TEST(ReflectedCallStatusError, copy_construct_on_stack___error_InstanceOnStackDisabledNoCopyCtor)
	//{
	//	{
	//		optional<Record> classCalender = MyReflection::instance().getRecord(calender::ns, calender::struct_);
	//		ASSERT_TRUE(classCalender);

	//		auto [status, srcObj] = classCalender->create<alloc::Stack>();
	//		ASSERT_TRUE(status == error::InstanceOnStackDisabledNoCopyCtor);
	//		ASSERT_TRUE(srcObj.isEmpty());
	//	}
	//	EXPECT_TRUE(calender::assert_zero_instance_count());
	//	EXPECT_TRUE(Instance::getInstanceCount() == 0);
	//}


	//TEST(ReflectedCallStatusError, static_method_call_wrong_args___error_SignatureMismatch)
	//{
	//	optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
	//	ASSERT_TRUE(classPerson);

	//	optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
	//	ASSERT_TRUE(getProfile);
	//	ASSERT_TRUE(getProfile->hasSignature<>());  //empty template params checks for zero arguments.

	//	const RStatus& status = getProfile->bind().call(std::string());

	//	ASSERT_TRUE(status == error::SignatureMismatch);
	//}


	//TEST(ReflectedCallStatusError, copy_ctor_on_empty_instance___error_EmptyInstance)
	//{
	//	{
	//		Instance emptyObj;
	//		ASSERT_TRUE(emptyObj.isEmpty());

	//		optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
	//		ASSERT_TRUE(classPerson);

	//		auto [status, personObj] = classPerson->clone(emptyObj);

	//		ASSERT_TRUE(status == error::EmptyInstance);
	//	}
	//	EXPECT_TRUE(Instance::getInstanceCount() == 0);
	//}


	//TEST(ReflectedCallStatusError, method_call_on_empty_instance___error_EmptyInstance)
	//{
	//	{
	//		Instance emptyObj;
	//		ASSERT_TRUE(emptyObj.isEmpty());

	//		optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
	//		ASSERT_TRUE(classBook);

	//		RStatus status = classBook->getMethod(book::str_getPublishedOn)->bind(emptyObj).call();
	//		ASSERT_TRUE(status == error::EmptyInstance);
	//	}
	//	EXPECT_TRUE(Instance::getInstanceCount() == 0);
	//}


	//TEST(ReflectedCallStatusError, method_on_wrong_heap_instance___error_InstanceTypeMismatch)
	//{
	//	{
	//		optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
	//		ASSERT_TRUE(classPerson);

	//		optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
	//		ASSERT_TRUE(classBook);

	//		auto [status, personObj] = classPerson->create<alloc::Heap>();
	//		ASSERT_TRUE(status);
	//		ASSERT_FALSE(personObj.isEmpty());

	//		optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
	//		ASSERT_TRUE(getPublishedOn);

	//		status = getPublishedOn->bind(personObj).call();
	//		ASSERT_TRUE(status == error::InstanceTypeMismatch);
	//	}
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//	EXPECT_TRUE(Instance::getInstanceCount() == 0);
	//}


	//TEST(ReflectedCallStatusError, method_on_wrong_stack_instance___error_InstanceTypeMismatch)
	//{
	//	{
	//		optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
	//		ASSERT_TRUE(classPerson);

	//		optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
	//		ASSERT_TRUE(classBook);

	//		auto [status, personObj] = classPerson->create<alloc::Stack>();
	//		ASSERT_TRUE(status);
	//		ASSERT_FALSE(personObj.isEmpty());

	//		optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
	//		ASSERT_TRUE(getPublishedOn);

	//		status = getPublishedOn->bind(personObj).call();
	//		ASSERT_TRUE(status == error::InstanceTypeMismatch);
	//	}
	//	EXPECT_TRUE(person::assert_zero_instance_count());
	//	EXPECT_TRUE(Instance::getInstanceCount() == 0);
	//}


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