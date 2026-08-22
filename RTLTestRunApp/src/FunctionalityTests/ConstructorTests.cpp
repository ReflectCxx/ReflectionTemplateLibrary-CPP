
#include <rtl_access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace rtl;

using namespace test_utils;


namespace rtl_tests 
{
	TEST(RTLInterfaceCxxMirror, get_record_types_with_wrong_names)
	{
		optional<Function> badFunc = cxx::mirror().getFunction("wrong_date_struct");
		EXPECT_FALSE(badFunc);

		optional<Record> badRec = cxx::mirror().getRecord("wrong" + std::string(cxx::type::nsdate::Date::id));
		EXPECT_FALSE(badRec);
	}


	TEST(HeapAllocConstructorDate, wrong_args)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			rtl::constructor<std::string, int> ctorT = classDate->ctorT<std::string, int>();
			auto [err, date] = ctorT(alloc::Heap, "wrong", 10);

			EXPECT_TRUE(err == error::SignatureMismatch);
			ASSERT_TRUE(date.isEmpty());
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, wrong_args)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			rtl::constructor<std::string, int> ctorT = classDate->ctorT<std::string, int>();
			auto [err, date] = ctorT(alloc::Stack, "wrong", 10);

			EXPECT_TRUE(err == error::SignatureMismatch);
			ASSERT_TRUE(date.isEmpty());
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorDate, args_void)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->ctorT()(alloc::Heap);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, args_void)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->ctorT()(alloc::Stack);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorDate, args_string)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			rtl::constructor<std::string> ctorT = classDate->ctorT<std::string>();
			auto [err, date] = ctorT(alloc::Heap, date::DATE_STR0.data());
			
			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<string>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, args_string)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			rtl::constructor<std::string> ctorT = classDate->ctorT<std::string>();
			auto [err, date] = ctorT(alloc::Stack, date::DATE_STR0.data());

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<string>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorDate, args_unsigned_unsigned_unsigned)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			auto ctorT = classDate->ctorT<unsigned, unsigned, unsigned>();
			auto [err, date] = ctorT(alloc::Heap, date::DAY, date::MONTH, date::YEAR);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(date.isEmpty());

			const bool isPassed = date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(date);
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, args_unsigned_unsigned_unsigned)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			unsigned day = date::DAY;
			unsigned month = date::MONTH;
			unsigned year = date::YEAR;

			auto ctorT = classDate->ctorT<unsigned, unsigned, unsigned>();
			auto [err, date] = ctorT(alloc::Stack, day, month, year);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(date.isEmpty());

			const bool isPassed = date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(date);
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(DestructorDate, non_virtual_on_heap)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->ctorT()(alloc::Heap);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(DestructorDate, non_virtual_on_stack)
	{
		{
			optional<Record> classDate = cxx::mirror().getRecord(cxx::type::nsdate::Date::id);
			ASSERT_TRUE(classDate);

			auto [err, date] = classDate->ctorT()(alloc::Stack);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(date.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(date));
		}
		EXPECT_TRUE(date::get_instance_count() == 0);
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, wrong_args)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->ctorT<float, int>()(alloc::Heap, 19.0, 87.5);

			EXPECT_TRUE(err == error::SignatureMismatch);
			ASSERT_TRUE(book.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, wrong_args)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->ctorT<float, int>()(alloc::Stack, 19.0, 87.5);

			EXPECT_TRUE(err == error::SignatureMismatch);
			ASSERT_TRUE(book.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, args_default)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->ctorT()(alloc::Heap);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, args_default)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->ctorT()(alloc::Stack);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, args_double_string)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
			ASSERT_TRUE(classBook);

			rtl::constructor<double, std::string> ctorT = classBook->ctorT<double, std::string>();
			auto [err, book] = ctorT(alloc::Heap, book::PRICE, book::TITLE.data());

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(book.isEmpty());
			
			const bool isPassed = book::test_dynamic_alloc_instance_ctor<double, string>(book);
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, args_double_string)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
			ASSERT_TRUE(classBook);

			rtl::constructor<double, std::string> ctorT = classBook->ctorT<double, std::string>();
			auto [err, book] = ctorT(alloc::Stack, book::PRICE, book::TITLE.data());

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(book.isEmpty());

			const bool isPassed = book::test_dynamic_alloc_instance_ctor<double, string>(book);
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(DestructorBook, non_virtual_on_heap)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->ctorT()(alloc::Heap);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(DestructorBook, non_virtual_on_stack)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
			ASSERT_TRUE(classBook);

			auto [err, book] = classBook->ctorT()(alloc::Stack);

			EXPECT_TRUE(err == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}
}