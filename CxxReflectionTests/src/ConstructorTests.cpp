#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests {

	TEST(RTLInterfaceCxxMirror, get_record_types_with_wrong_names)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Function> noFunc = cxxMirror.getFunction(date::ns, "wrong_date_struct");
		EXPECT_FALSE(noFunc.has_value());

		optional<Record> noRec = cxxMirror.getRecord(date::ns, "wrong" + std::string(date::struct_));
		EXPECT_FALSE(noRec.has_value());
	}


	TEST(HeapConstructorDate, wrong_args)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			EXPECT_TRUE(date::assert_zero_instance_count());
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();

			EXPECT_TRUE(date::assert_zero_instance_count());
			SmartAny instance = classDate.newInstance("wrong", "args0", 10);

			ASSERT_FALSE(instance.get().has_value());
			EXPECT_TRUE(date::assert_zero_instance_count());
		}
	}


	TEST(HeapConstructorDate, args_void)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			EXPECT_TRUE(date::assert_zero_instance_count());
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();
			SmartAny instance = classDate.newInstance();

			ASSERT_TRUE(instance.get().has_value());
			EXPECT_TRUE(date::test_heap_instance_ctor<>(instance.get()));
		}
	}


	TEST(HeapConstructorDate, args_string)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			EXPECT_TRUE(date::assert_zero_instance_count());
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();
			const string& dateStr = date::DATE_STR;
			SmartAny instance = classDate.newInstance(dateStr);

			ASSERT_TRUE(instance.get().has_value());
			EXPECT_TRUE(date::test_heap_instance_ctor<string>(instance.get()));
		}
	}


	TEST(HeapConstructorDate, args_unsigned_unsigned_unsigned)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			EXPECT_TRUE(date::assert_zero_instance_count());
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();
			SmartAny instance = classDate.newInstance(date::day, date::month, date::year);

			ASSERT_TRUE(instance.get().has_value());

			const bool isPassed = date::test_heap_instance_ctor<unsigned, unsigned, unsigned>(instance.get());
			EXPECT_TRUE(isPassed);
		}
	}

	
	TEST(StackConstructorDate, args_void)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();
			SmartAny instance = classDate.instance();

			ASSERT_TRUE(instance.get().has_value());
			EXPECT_TRUE(date::test_stack_instance_ctor<>(instance.get()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(StackConstructorDate, args_string)
	{
		EXPECT_TRUE(date::assert_zero_instance_count()); 
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();
			const string& dateStr = date::DATE_STR;
			SmartAny instance = classDate.instance(dateStr);

			ASSERT_TRUE(instance.get().has_value());
			EXPECT_TRUE(date::test_stack_instance_ctor<string>(instance.get()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(StackConstructorDate, args_unsigned_unsigned_unsigned)
	{
		EXPECT_TRUE(date::assert_zero_instance_count()); 
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();
			SmartAny instance = classDate.instance(date::day, date::month, date::year);

			ASSERT_TRUE(instance.get().has_value());

			const bool isPassed = date::test_stack_instance_ctor<unsigned, unsigned, unsigned>(instance.get());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(DestructorDate, non_virtual)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();
			SmartAny instance = classDate.newInstance();
			ASSERT_TRUE(instance.get().has_value());
			EXPECT_TRUE(date::test_heap_instance_ctor<>(instance.get()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(HeapConstructorBook, wrong_args)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(record.has_value());

			const Record& classBook = record.value();

			EXPECT_TRUE(book::assert_zero_instance_count());
			SmartAny instance = classBook.newInstance(19.0, 87.5);

			ASSERT_FALSE(instance.get().has_value());
			EXPECT_TRUE(book::assert_zero_instance_count());
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(HeapConstructorBook, args_default)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(record.has_value());

			const Record& classBook = record.value();
			SmartAny instance = classBook.newInstance();

			ASSERT_TRUE(instance.get().has_value());
			EXPECT_TRUE(book::test_heap_instance_ctor(instance.get()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(HeapConstructorBook, args_double_string)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(record.has_value());

			double price = book::PRICE;
			string title = book::TITLE;
			const Record& classBook = record.value();

			SmartAny instance = classBook.newInstance(price, title);
			ASSERT_TRUE(instance.get().has_value());

			const bool isPassed = book::test_heap_instance_ctor<double, string>(instance.get());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(StackConstructorBook, args_default)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(record.has_value());

			const Record& classBook = record.value();
			SmartAny instance = classBook.instance();

			ASSERT_TRUE(instance.get().has_value());
			EXPECT_TRUE(book::test_stack_instance_ctor(instance.get()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(StackConstructorBook, args_double_string)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(record.has_value());

			double price = book::PRICE;
			string title = book::TITLE;
			const Record& classBook = record.value();

			SmartAny instance = classBook.instance(price, title);
			ASSERT_TRUE(instance.get().has_value());

			const bool isPassed = book::test_stack_instance_ctor<double, string>(instance.get());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(DestructorBook, non_virtual)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> record = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(record.has_value());

			const Record& classDate = record.value();
			SmartAny instance = classDate.newInstance();
			ASSERT_TRUE(instance.get().has_value());
			EXPECT_TRUE(book::test_heap_instance_ctor(instance.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}
}