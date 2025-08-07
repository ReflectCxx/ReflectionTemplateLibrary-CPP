#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(RTLInterfaceCxxMirror, get_record_types_with_wrong_names)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> badFunc = cxxMirror.getFunction(date::ns, "wrong_date_struct");
		EXPECT_FALSE(badFunc);

		optional<Record> badRec = cxxMirror.getRecord(date::ns, "wrong" + std::string(date::struct_));
		EXPECT_FALSE(badRec);
	}


	TEST(HeapAllocConstructorDate, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->create<alloc::Heap>("wrong", "args0", 10);

			EXPECT_TRUE(err == error::SignatureMismatch);
			EXPECT_TRUE(date.isEmpty());
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->create<alloc::Stack>("wrong", "args0", 10);

			EXPECT_TRUE(err == error::SignatureMismatch);
			EXPECT_TRUE(date.isEmpty());
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorDate, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->create<alloc::Heap>();

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->create<alloc::Stack>();

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorDate, args_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			string dateStr = date::DATE_STR0;
			auto [err, date] = classDate->create<alloc::Heap>(dateStr);
			
			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<string>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, args_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			string dateStr = date::DATE_STR0;
			auto [err, date] = classDate->create<alloc::Stack>(dateStr);

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<string>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorDate, args_unsigned_unsigned_unsigned)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			unsigned day = date::DAY;
			unsigned month = date::MONTH;
			unsigned year = date::YEAR;

			auto [err, date] = classDate->create<alloc::Heap>(day, month, year);

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(date.isEmpty());

			const bool isPassed = date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(date);
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, args_unsigned_unsigned_unsigned)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			unsigned day = date::DAY;
			unsigned month = date::MONTH;
			unsigned year = date::YEAR;

			auto [err, date] = classDate->create<alloc::Stack>(day, month, year);

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(date.isEmpty());

			const bool isPassed = date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(date);
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(DestructorDate, non_virtual_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->create<alloc::Heap>();

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(DestructorDate, non_virtual_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->create<alloc::Stack>();

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->create<alloc::Heap>(19.0, 87.5);

			EXPECT_TRUE(err == error::SignatureMismatch);
			EXPECT_TRUE(book.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->create<alloc::Stack>(19.0, 87.5);

			EXPECT_TRUE(err == error::SignatureMismatch);
			EXPECT_TRUE(book.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, args_default)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(book.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, args_default)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(book.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, args_double_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			double price = book::PRICE;
			string title = book::TITLE;
			auto [err, book] = classBook->create<alloc::Heap>(price, title);

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(book.isEmpty());
			
			const bool isPassed = book::test_dynamic_alloc_instance_ctor<double, string>(book);
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, args_double_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			double price = book::PRICE;
			string title = book::TITLE;
			auto [err, book] = classBook->create<alloc::Stack>(price, title);

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(book.isEmpty());

			const bool isPassed = book::test_dynamic_alloc_instance_ctor<double, string>(book);
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(DestructorBook, non_virtual_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(book.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}


	TEST(DestructorBook, non_virtual_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err == error::None);
			EXPECT_FALSE(book.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
	}
}