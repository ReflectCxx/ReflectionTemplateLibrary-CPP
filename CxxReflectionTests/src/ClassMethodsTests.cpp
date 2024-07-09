#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(RTLInterfaceCxxMirror, get_class_methods_with_wrong_names)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();
		optional<Method> badMethod = classBook.getMethod("no_method");
		EXPECT_FALSE(badMethod.has_value());
	}


	TEST(ReflectionMethodCall, wrong_args)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_setAuthor);
			ASSERT_TRUE(methOpt.has_value());

			auto [status, bookObj] = classBook.instance();
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(bookObj.isEmpty());

			const char* authorStr = book::AUTHOR;
			const Method& setAuthor = methOpt.value();

			ASSERT_FALSE(setAuthor.hasSignature<const char*>());

			RStatus retObj = setAuthor(bookObj)(authorStr);
			ASSERT_FALSE(retObj.didCallSucceed());
			ASSERT_FALSE(retObj.get().has_value());
			EXPECT_FALSE(book::test_method_setAuthor(bookObj.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethod, args_void)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(methOpt.has_value());

			auto [status, bookObj] = classBook.instance();
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(bookObj.isEmpty());

			const Method& getPublishedOn = methOpt.value();
			ASSERT_TRUE(getPublishedOn.hasSignature<void>());

			RStatus retObj = getPublishedOn(bookObj)();
			ASSERT_TRUE(retObj.didCallSucceed());
			ASSERT_TRUE(retObj.get().has_value()); 
			ASSERT_TRUE(retObj.isOfType<string>());

			const std::string& retStr = any_cast<string>(retObj.get());
			EXPECT_TRUE(book::test_method_getPublishedOn_return(retStr));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethod, args_string)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_setAuthor);
			ASSERT_TRUE(methOpt.has_value());

			auto [status, bookObj] = classBook.instance();
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(bookObj.isEmpty());
			
			const Method& setAuthor = methOpt.value();
			ASSERT_TRUE(setAuthor.hasSignature<std::string>());

			std::string authorStr = book::AUTHOR;
			RStatus retObj = setAuthor(bookObj)(authorStr);

			ASSERT_TRUE(retObj.didCallSucceed());
			ASSERT_FALSE(retObj.get().has_value());

			EXPECT_TRUE(book::test_method_setAuthor(bookObj.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethodOverload, args_void)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(methOpt.has_value());

			auto [status, bookObj] = classBook.instance();
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(bookObj.isEmpty());

			const Method& updateBookInfo = methOpt.value();
			ASSERT_TRUE(updateBookInfo.hasSignature<void>());
			
			RStatus retObj = updateBookInfo(bookObj)();
			ASSERT_TRUE(retObj.didCallSucceed());
			ASSERT_FALSE(retObj.get().has_value());

			EXPECT_TRUE(book::test_method_updateBookInfo(bookObj.get()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethodOverload, args_string_double_charPtr)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(methOpt.has_value());

			auto [status, bookObj] = classBook.instance();
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(bookObj.isEmpty());

			const Method& updateBookInfo = methOpt.value();
			const bool signatureValid = updateBookInfo.hasSignature<string, double, const char*>();
			ASSERT_TRUE(signatureValid);

			string author = book::AUTHOR;
			RStatus retObj = updateBookInfo(bookObj)(author, book::PRICE, book::TITLE);
			ASSERT_TRUE(retObj.didCallSucceed());
			ASSERT_FALSE(retObj.get().has_value());

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

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(methOpt.has_value());

			auto [status, bookObj] = classBook.instance();
			ASSERT_TRUE(status.didCallSucceed());
			ASSERT_FALSE(bookObj.isEmpty());

			const Method& updateBookInfo = methOpt.value();
			const bool signatureValid = updateBookInfo.hasSignature<const char*, double, string>();
			ASSERT_TRUE(signatureValid);

			string author = book::AUTHOR;
			RStatus retObj = updateBookInfo(bookObj)(book::TITLE, book::PRICE, author);
			ASSERT_TRUE(retObj.didCallSucceed());
			ASSERT_FALSE(retObj.get().has_value());

			const bool isSuccess = book::test_method_updateBookInfo<const char*, double, string>(bookObj.get());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}
}