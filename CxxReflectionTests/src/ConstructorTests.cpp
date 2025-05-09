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

			auto [status, instance] = classDate->instance<alloc::Heap>("wrong", "args0", 10);

			ASSERT_TRUE(status == Error::SignatureMismatch);
			ASSERT_TRUE(instance.isEmpty());
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance<alloc::Stack>("wrong", "args0", 10);

			ASSERT_TRUE(status == Error::SignatureMismatch);
			ASSERT_TRUE(instance.isEmpty());
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorDate, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorDate, args_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			string dateStr = date::DATE_STR0;
			auto [status, instance] = classDate->instance<alloc::Heap>(dateStr);
			
			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<string>(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(StackAllocConstructorDate, args_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			string dateStr = date::DATE_STR0;
			auto [status, instance] = classDate->instance<alloc::Stack>(dateStr);

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<string>(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
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

			auto [status, instance] = classDate->instance<alloc::Heap>(day, month, year);

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());

			const bool isPassed = date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(instance.get(), instance.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
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

			auto [status, instance] = classDate->instance<alloc::Stack>(day, month, year);

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());

			const bool isPassed = date::test_dynamic_alloc_instance_ctor<unsigned, unsigned, unsigned>(instance.get(), instance.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DestructorDate, non_virtual_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DestructorDate, non_virtual_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classDate = cxxMirror.getRecord(date::ns, date::struct_);
			ASSERT_TRUE(classDate);

			auto [status, instance] = classDate->instance<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(date::test_dynamic_alloc_instance_ctor<>(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(date::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance<alloc::Heap>(19.0, 87.5);

			ASSERT_TRUE(status == Error::SignatureMismatch);
			ASSERT_TRUE(instance.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance<alloc::Stack>(19.0, 87.5);

			ASSERT_TRUE(status == Error::SignatureMismatch);
			ASSERT_TRUE(instance.isEmpty());
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, args_default)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, args_default)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(HeapAllocConstructorBook, args_double_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			double price = book::PRICE;
			string title = book::TITLE;
			auto [status, instance] = classBook->instance<alloc::Heap>(price, title);

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			
			const bool isPassed = book::test_dynamic_alloc_instance_ctor<double, string>(instance.get(), instance.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(StackAllocConstructorBook, args_double_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			double price = book::PRICE;
			string title = book::TITLE;
			auto [status, instance] = classBook->instance<alloc::Stack>(price, title);

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());

			const bool isPassed = book::test_dynamic_alloc_instance_ctor<double, string>(instance.get(), instance.isOnHeap());
			EXPECT_TRUE(isPassed);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DestructorBook, non_virtual_on_heap)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(DestructorBook, non_virtual_on_stack)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			auto [status, instance] = classBook->instance<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(instance.isEmpty());
			EXPECT_TRUE(book::test_dynamic_alloc_instance_ctor(instance.get(), instance.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}
}