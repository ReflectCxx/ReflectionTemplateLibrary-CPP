#include <gtest/gtest.h>

#include "Reflection.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests {

	TEST(ConstructorDate, args_void)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord(date::NS_DATE, "Date");
		ASSERT_TRUE(record.has_value());

		const Record& classDate = record.value();
		unique_ptr<RObject> instance = classDate.newInstance();

		ASSERT_TRUE(instance != nullptr);
		EXPECT_TRUE(date::test_new_instance_ctor<>(instance));
	}


	TEST(ConstructorDate, args_string)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord(date::NS_DATE, "Date");
		ASSERT_TRUE(record.has_value());

		const Record& classDate = record.value();
		const string& dateStr = date::DATE_STR;
		unique_ptr<RObject> instance = classDate.newInstance(dateStr);

		ASSERT_TRUE(instance != nullptr);
		EXPECT_TRUE(date::test_new_instance_ctor<string>(instance));
	}


	TEST(ConstructorDate, args_unsigned_unsigned_unsigned)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord(date::NS_DATE, "Date");
		ASSERT_TRUE(record.has_value());

		const Record& classDate = record.value();
		unique_ptr<RObject> instance = classDate.newInstance(date::day, date::month, date::year);

		ASSERT_TRUE(instance != nullptr);

		const bool isPassed = date::test_new_instance_ctor<unsigned, unsigned, unsigned>(instance);
		EXPECT_TRUE(isPassed);
	}

	
	TEST(DestructorDate, non_virtual)
	{
		EXPECT_TRUE(date::assert_zero_instance_count());

		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord(date::NS_DATE, "Date");
		ASSERT_TRUE(record.has_value());
		{
			const Record& classDate = record.value();
			unique_ptr<RObject> instance = classDate.newInstance();
			ASSERT_TRUE(instance != nullptr);
			EXPECT_TRUE(date::test_new_instance_ctor<>(instance));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
	}


	TEST(ConstructorBook, args_default)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord("Book");
		ASSERT_TRUE(record.has_value());

		const Record& classBook = record.value();
		unique_ptr<RObject> instance = classBook.newInstance();

		ASSERT_TRUE(instance != nullptr);
		EXPECT_TRUE(book::test_new_instance_ctor(instance));
	}


	TEST(ConstructorBook, args_double_string)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord("Book");
		ASSERT_TRUE(record.has_value());

		double price = book::PRICE;
		string title = book::TITLE;
		const Record& classBook = record.value();

		unique_ptr<RObject> instance = classBook.newInstance(price, title);
		ASSERT_TRUE(instance != nullptr);

		const bool isPassed = book::test_new_instance_ctor<double, string>(instance);
		EXPECT_TRUE(isPassed);
	}


	TEST(DestructorBook, non_virtual)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());

		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord("Book");
		ASSERT_TRUE(record.has_value());
		{
			const Record& classDate = record.value();
			unique_ptr<RObject> instance = classDate.newInstance();
			ASSERT_TRUE(instance != nullptr);
			EXPECT_TRUE(book::test_new_instance_ctor(instance));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}
}