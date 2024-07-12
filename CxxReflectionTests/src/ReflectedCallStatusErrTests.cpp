
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
	TEST(ReflectedCallStatusError, unregistered_constructor___error_ConstructorNotFound)
	{
		optional<Record> classLibrary = MyReflection::instance().getRecord(library::class_);
		ASSERT_TRUE(classLibrary);

		auto [status, instance] = classLibrary->instance();

		ASSERT_TRUE(status == Error::ConstructorNotFound);
		ASSERT_TRUE(instance.isEmpty());
	}


	TEST(ReflectedCallStatusError, unregistered_constructor___error_CopyConstructorNotFound)
	{
		EXPECT_TRUE(calender::assert_zero_instance_count());
		{
			optional<Record> classCalender = MyReflection::instance().getRecord(calender::ns, calender::struct_);
			ASSERT_TRUE(classCalender);

			auto [ret, srcObj] = classCalender->instance();
			ASSERT_TRUE(ret);
			ASSERT_FALSE(srcObj.isEmpty());

			auto [status, instance] = classCalender->clone(srcObj);

			ASSERT_TRUE(status == Error::CopyConstructorNotFound);
			ASSERT_TRUE(instance.isEmpty());
		}
		EXPECT_TRUE(calender::assert_zero_instance_count());
	}


	TEST(ReflectedCallStatusError, static_method_call_wrong_args___error_SignatureMismatch)
	{
		optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		optional<Method> getProfile = classPerson->getMethod(person::str_getProfile);
		ASSERT_TRUE(getProfile);
		ASSERT_TRUE(getProfile->hasSignature<void>());

		const RStatus& status = getProfile->on().call(std::string());

		ASSERT_TRUE(status == Error::SignatureMismatch);
	}


	TEST(ReflectedCallStatusError, copy_ctor_on_empty_instance___error_EmptyInstance)
	{
		optional<Record> classLibrary = MyReflection::instance().getRecord(library::class_);
		ASSERT_TRUE(classLibrary);

		auto [status, emptyObj] = classLibrary->instance();

		ASSERT_TRUE(status == Error::ConstructorNotFound);
		ASSERT_TRUE(emptyObj.isEmpty());

		optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
		ASSERT_TRUE(classPerson);

		auto [retStatus, personObj] = classPerson->clone(emptyObj);

		ASSERT_TRUE(retStatus == Error::EmptyInstance);
	}


	TEST(ReflectedCallStatusError, method_call_on_empty_instance___error_EmptyInstance)
	{
		optional<Record> classLibrary = MyReflection::instance().getRecord(library::class_);
		ASSERT_TRUE(classLibrary);

		auto [ret, emptyObj] = classLibrary->instance();

		ASSERT_TRUE(ret == Error::ConstructorNotFound);
		ASSERT_TRUE(emptyObj.isEmpty());

		optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
		ASSERT_TRUE(classBook);

		RStatus retStatus = classBook->getMethod(book::str_getPublishedOn)->on(emptyObj).call();
		ASSERT_TRUE(retStatus == Error::EmptyInstance);
	}


	TEST(ReflectedCallStatusError, unregistered_constructor___error_ConstCopyConstructorNotFound)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			optional<Record> classDate = MyReflection::instance().getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [ret, srcObj] = classDate->instance();
			ASSERT_TRUE(ret);
			ASSERT_FALSE(srcObj.isEmpty());

			srcObj.makeConst();

			auto [status, instance] = classDate->clone(srcObj);

			ASSERT_TRUE(status == Error::ConstCopyConstructorNotFound);
			ASSERT_TRUE(instance.isEmpty());
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(ReflectedCallStatusError, method_on_wrong_instance___error_InstanceTypeMismatch)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{
			optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, personObj] = classPerson->instance();
			ASSERT_TRUE(status);
			ASSERT_FALSE(personObj.isEmpty());

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			RStatus retStatus = getPublishedOn->on(personObj).call();
			ASSERT_TRUE(retStatus == Error::InstanceTypeMismatch);
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}


	TEST(ReflectedCallStatusError, non_const_method_on_const_Instance__error_InstanceConstMismatch)
	{
		EXPECT_TRUE(person::assert_zero_instance_count());
		{	
			optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, bookObj] = classBook->instance();
			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			bookObj.makeConst();
			RStatus retStatus = getPublishedOn->on(bookObj).call();

			ASSERT_TRUE(retStatus == Error::InstanceConstMismatch);
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
	}
}