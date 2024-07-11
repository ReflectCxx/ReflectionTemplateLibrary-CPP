#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(RTLInterfaceCxxMirror, get_class_methods_with_wrong_names)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> classBook = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(classBook);

		optional<Method> badMethod = classBook->getMethod("no_method");
		EXPECT_FALSE(badMethod.has_value());
	}


	TEST(ReflectionMethodCall, wrong_args)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [status, bookObj] = classBook->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_FALSE(setAuthor->hasSignature<const char*>());

			RStatus rStatus = (*setAuthor)(bookObj)(book::AUTHOR);

			ASSERT_TRUE(rStatus == rtl::Error::SignatureMismatch);
			ASSERT_FALSE(rStatus.getReturn().has_value());
			EXPECT_FALSE(book::test_method_setAuthor(bookObj.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethod, args_void)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			auto [status, bookObj] = classBook->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(getPublishedOn->hasSignature<void>());

			RStatus rStatus = (*getPublishedOn)(bookObj)();

			ASSERT_TRUE(rStatus);
			ASSERT_TRUE(rStatus.getReturn().has_value()); 
			ASSERT_TRUE(rStatus.isOfType<string>());

			const std::string& retStr = any_cast<string>(rStatus.getReturn());
			EXPECT_TRUE(book::test_method_getPublishedOn_return(retStr));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethod, args_string)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [status, bookObj] = classBook->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(setAuthor->hasSignature<std::string>());

			RStatus rStatus = (*setAuthor)(bookObj)(std::string(book::AUTHOR));

			ASSERT_TRUE(rStatus);
			ASSERT_FALSE(rStatus.getReturn().has_value());

			EXPECT_TRUE(book::test_method_setAuthor(bookObj.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethodOverload, args_void)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(updateBookInfo->hasSignature<void>());
			
			RStatus rStatus = (*updateBookInfo)(bookObj)();

			ASSERT_TRUE(rStatus);
			ASSERT_FALSE(rStatus.getReturn().has_value());
			EXPECT_TRUE(book::test_method_updateBookInfo(bookObj.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethodOverload, args_string_double_charPtr)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			const bool signatureValid = updateBookInfo->hasSignature<string, double, const char*>();
			ASSERT_TRUE(signatureValid);

			RStatus rStatus = (*updateBookInfo)(bookObj)(string(book::AUTHOR), book::PRICE, book::TITLE);

			ASSERT_TRUE(rStatus);
			ASSERT_FALSE(rStatus.getReturn().has_value());
			const bool isSuccess = book::test_method_updateBookInfo<string, double, const char*>(bookObj.get());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethodOverload, args_charPtr_double_string)
	{
		EXPECT_TRUE(book::assert_zero_instance_count()); 
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			const bool signatureValid = updateBookInfo->hasSignature<const char*, double, string>();
			ASSERT_TRUE(signatureValid);

			RStatus rStatus = (*updateBookInfo)(bookObj)(book::TITLE, book::PRICE, string(book::AUTHOR));

			ASSERT_TRUE(rStatus);
			ASSERT_FALSE(rStatus.getReturn().has_value());
			const bool isSuccess = book::test_method_updateBookInfo<const char*, double, string>(bookObj.get());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}
}