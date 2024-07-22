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


	TEST(DynamicAllocConstructorDate, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance("wrong", "args0", 10);

			ASSERT_TRUE(status == Error::SignatureMismatch);
			ASSERT_TRUE(instance.isEmpty());
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DynamicAllocConstructorDate, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(instance.get()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DynamicAllocConstructorDate, args_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			const string& dateStr = date::DATE_STR;
			auto [status, instance] = classDate->instance(dateStr);
			
			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<string>(instance.get()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DynamicAllocConstructorDate, args_unsigned_unsigned_unsigned)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance(date::DAY, date::MONTH, date::YEAR);

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());

			const bool isPassed = date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(instance.get());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DestructorDate, non_virtual)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(instance.get()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DynamicAllocConstructorBook, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance(19.0, 87.5);

			ASSERT_TRUE(status == Error::SignatureMismatch);
			ASSERT_TRUE(instance.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DynamicAllocConstructorBook, args_default)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(instance.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DynamicAllocConstructorBook, args_double_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			double price = book::PRICE;
			string title = book::TITLE;
			auto [status, instance] = classBook->instance(price, title);

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			
			const bool isPassed = book::test_dynamic_alloc_instance_ctor<double, string>(instance.get());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DestructorBook, non_virtual)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(instance.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}
}