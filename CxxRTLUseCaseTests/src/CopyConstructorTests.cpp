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

			auto [err0, book] = classBook->create<alloc::Heap>();
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			auto [err1, badObj] = classPerson->clone(book);

			ASSERT_TRUE(err1 == error::MethodTargetMismatch);
			ASSERT_TRUE(badObj.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(CopyConstructor, call_copy_ctor_of_PERSON_with_BOOK_instance_on_stack)
	{
		{
			optional<Record> classPerson = MyReflection::instance().getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err0, book] = classBook->create<alloc::Stack>();
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			auto [err1, badObj] = classPerson->clone(book);

			ASSERT_TRUE(err1 == error::MethodTargetMismatch);
			ASSERT_TRUE(badObj.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
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

			auto [err0, book] = classBook->create<alloc::Heap>(price, title);
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			auto [err1, ret1] = (*setAuthor)(book)(author);
			ASSERT_TRUE(err1 == error::None);

			auto [err2, ret2] = (*setDecription)(book)(description);
			ASSERT_TRUE(err1 == error::None);

			auto [err3, bookCopy] = classBook->clone(book);
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(bookCopy.isEmpty());

			const bool isPassed = book::test_unique_copy_ctor_const_ref(bookCopy.get(), bookCopy.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
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

			auto [err0, book] = classBook->create<alloc::Stack>(price, title);
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			auto [err1, ret1] = (*setAuthor)(book)(author);
			ASSERT_TRUE(err1 == error::None);

			auto [err2, ret2] = (*setDecription)(book)(description);
			ASSERT_TRUE(err1 == error::None);

			auto [err3, bookCopy] = classBook->clone(book);
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(bookCopy.isEmpty());

			const bool isPassed = book::test_unique_copy_ctor_const_ref(bookCopy.get(), bookCopy.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_non_const_ref_overload___src_instance_non_const_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			auto [err0, person] = classPerson->create<alloc::Heap>();
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());

			auto [err1, personCopy] = classPerson->clone(person);
			ASSERT_TRUE(err1 == error::None);
			ASSERT_FALSE(personCopy.isEmpty());

			const bool isPassed = person::test_copy_constructor_overload_src_non_const_obj(personCopy.get(), personCopy.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(CopyConstructor, copy_ctor_arg_non_const_ref_overload___src_instance_non_const_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
			ASSERT_TRUE(classPerson);

			auto [err0, person] = classPerson->create<alloc::Stack>();
			ASSERT_TRUE(err0 == error::None);
			ASSERT_FALSE(person.isEmpty());

			auto [err1, personCopy] = classPerson->clone(person);
			ASSERT_TRUE(err1 == error::None);
			ASSERT_FALSE(personCopy.isEmpty());

			const bool isPassed = person::test_copy_constructor_overload_src_non_const_obj(personCopy.get(), personCopy.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(person::assert_zero_instance_count());
		EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}
}