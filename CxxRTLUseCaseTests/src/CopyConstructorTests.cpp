#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"
#include "TestUtilsPerson.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests
{

	TEST(CopyConstructor, call_copy_ctor_of_PERSON_with_BOOK_instance_on_heap)
	{
		{
			optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, bookObj] = classBook->instance<rtl::alloc::Heap>();
			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());

			auto [retStatus, badObj] = classPerson->clone(bookObj);

			ASSERT_TRUE(retStatus == Error::InstanceTypeMismatch);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, call_copy_ctor_of_PERSON_with_BOOK_instance_on_stack)
	{
		{
			optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, bookObj] = classBook->instance<rtl::alloc::Stack>();
			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());

			auto [retStatus, badObj] = classPerson->clone(bookObj);

			ASSERT_TRUE(retStatus == Error::InstanceTypeMismatch);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_const_ref___src_instance_non_const_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			optional<Method> setDecription = classBook->getMethod(book::str_setDescription);
			ASSERT_TRUE(setDecription);

			double price = book::PRICE;
			string title = book::TITLE;
			string author = book::AUTHOR;
			string description = book::DESCRIPTION;

			auto [status, srcObj] = classBook->instance<rtl::alloc::Heap>(price, title);
			ASSERT_TRUE(status);
			ASSERT_FALSE(srcObj.isEmpty());

			status = (*setAuthor)(srcObj)(author);
			ASSERT_TRUE(status);

			status = (*setDecription)(srcObj)(description);
			ASSERT_TRUE(status);

			auto [ret, copyObj] = classBook->clone(srcObj);
			ASSERT_TRUE(ret);
			ASSERT_FALSE(copyObj.isEmpty());

			const bool isPassed = book::test_unique_copy_ctor_const_ref(copyObj.get(), copyObj.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_const_ref___src_instance_non_const_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			optional<Method> setDecription = classBook->getMethod(book::str_setDescription);
			ASSERT_TRUE(setDecription);

			double price = book::PRICE;
			string title = book::TITLE;
			string author = book::AUTHOR;
			string description = book::DESCRIPTION;

			auto [status, srcObj] = classBook->instance<rtl::alloc::Stack>(price, title);
			ASSERT_TRUE(status);
			ASSERT_FALSE(srcObj.isEmpty());

			status = (*setAuthor)(srcObj)(author);
			ASSERT_TRUE(status);

			status = (*setDecription)(srcObj)(description);
			ASSERT_TRUE(status);

			auto [ret, copyObj] = classBook->clone(srcObj);
			ASSERT_TRUE(ret);
			ASSERT_FALSE(copyObj.isEmpty());

			const bool isPassed = book::test_unique_copy_ctor_const_ref(copyObj.get(), copyObj.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_const_ref___src_instance_const_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			optional<Method> setDecription = classBook->getMethod(book::str_setDescription);
			ASSERT_TRUE(setDecription);

			double price = book::PRICE;
			string title = book::TITLE;
			string author = book::AUTHOR;
			string description = book::DESCRIPTION;

			auto [status, srcObj] = classBook->instance<rtl::alloc::Heap>(price, title);
			ASSERT_TRUE(status);
			ASSERT_FALSE(srcObj.isEmpty());

			status = (*setAuthor)(srcObj)(author);
			ASSERT_TRUE(status);

			status = (*setDecription)(srcObj)(description);
			ASSERT_TRUE(status);

			//make this instance const.
			srcObj.makeConst();

			auto [ret, copyObj] = classBook->clone(srcObj);
			ASSERT_TRUE(ret);
			ASSERT_FALSE(copyObj.isEmpty());

			const bool isPassed = book::test_unique_copy_ctor_const_ref(copyObj.get(), copyObj.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_const_ref___src_instance_const_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			optional<Method> setDecription = classBook->getMethod(book::str_setDescription);
			ASSERT_TRUE(setDecription);

			double price = book::PRICE;
			string title = book::TITLE;
			string author = book::AUTHOR;
			string description = book::DESCRIPTION;

			auto [status, srcObj] = classBook->instance<rtl::alloc::Stack>(price, title);
			ASSERT_TRUE(status);
			ASSERT_FALSE(srcObj.isEmpty());

			status = (*setAuthor)(srcObj)(author);
			ASSERT_TRUE(status);

			status = (*setDecription)(srcObj)(description);
			ASSERT_TRUE(status);

			//make this instance const.
			srcObj.makeConst();

			auto [ret, copyObj] = classBook->clone(srcObj);
			ASSERT_TRUE(ret);
			ASSERT_FALSE(copyObj.isEmpty());

			const bool isPassed = book::test_unique_copy_ctor_const_ref(copyObj.get(), copyObj.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_const_ref_overload___src_instance_const_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			auto [status, srcObj] = classPerson->instance<rtl::alloc::Heap>();
			ASSERT_TRUE(status);
			ASSERT_FALSE(srcObj.isEmpty());

			srcObj.makeConst();

			auto [ret, copyObj] = classPerson->clone(srcObj);
			ASSERT_TRUE(ret);
			ASSERT_FALSE(copyObj.isEmpty());

			const bool isPassed = person::test_copy_constructor_overload_src_const_obj(copyObj.get(), copyObj.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_const_ref_overload___src_instance_const_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			auto [status, srcObj] = classPerson->instance<rtl::alloc::Stack>();
			ASSERT_TRUE(status);
			ASSERT_FALSE(srcObj.isEmpty());

			srcObj.makeConst();

			auto [ret, copyObj] = classPerson->clone(srcObj);
			ASSERT_TRUE(ret);
			ASSERT_FALSE(copyObj.isEmpty());

			const bool isPassed = person::test_copy_constructor_overload_src_const_obj(copyObj.get(), copyObj.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_non_const_ref_overload___src_instance_non_const_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			auto [status, srcObj] = classPerson->instance<rtl::alloc::Heap>();
			ASSERT_TRUE(status);
			ASSERT_FALSE(srcObj.isEmpty());

			auto [ret, copyObj] = classPerson->clone(srcObj);
			ASSERT_TRUE(ret);
			ASSERT_FALSE(copyObj.isEmpty());

			const bool isPassed = person::test_copy_constructor_overload_src_non_const_obj(copyObj.get(), copyObj.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_non_const_ref_overload___src_instance_non_const_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			auto [status, srcObj] = classPerson->instance<rtl::alloc::Stack>();
			ASSERT_TRUE(status);
			ASSERT_FALSE(srcObj.isEmpty());

			auto [ret, copyObj] = classPerson->clone(srcObj);
			ASSERT_TRUE(ret);
			ASSERT_FALSE(copyObj.isEmpty());

			const bool isPassed = person::test_copy_constructor_overload_src_non_const_obj(copyObj.get(), copyObj.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}
}