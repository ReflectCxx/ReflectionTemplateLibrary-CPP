#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests {

	TEST(RTLInterfaceCxxMirror, get_class_methods_with_wrong_names)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();
		optional<Method> noMethod = classBook.getMethod("no_method");
		EXPECT_FALSE(noMethod.has_value());
	}


	TEST(ClassBookMethod, wrong_args)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_setAuthor);
		ASSERT_TRUE(methOpt.has_value());

		SmartAny bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj.get().has_value());

		const char* authorStr = book::AUTHOR;
		const Method& setAuthor = methOpt.value();

		SmartAny retObj = setAuthor(bookObj).invoke(authorStr);
		ASSERT_FALSE(retObj.get().has_value());

		EXPECT_FALSE(book::test_method_setAuthor(bookObj.get()));
	}


	TEST(ClassBookMethod, args_void)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_getPublishedOn);
		ASSERT_TRUE(methOpt.has_value());

		SmartAny bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj.get().has_value());

		const Method& getPublishedOn = methOpt.value();
		SmartAny retObj = getPublishedOn(bookObj).invoke();

		ASSERT_TRUE(retObj.get().has_value() && retObj.isOfType<string>());

		const std::string& retStr = any_cast<string>(retObj.get());
		EXPECT_TRUE(book::test_method_getPublishedOn_return(retStr));
	}


	TEST(ClassBookMethod, args_string)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_setAuthor);
		ASSERT_TRUE(methOpt.has_value());

		SmartAny bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj.get().has_value());

		std::string authorStr = book::AUTHOR;
		const Method& setAuthor = methOpt.value();

		SmartAny retObj = setAuthor(bookObj).invoke(authorStr);
		ASSERT_FALSE(retObj.get().has_value());

		EXPECT_TRUE(book::test_method_setAuthor(bookObj.get()));
	}


	TEST(ClassBookMethodOverload, args_void)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
		ASSERT_TRUE(methOpt.has_value());

		SmartAny bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj.get().has_value());

		const Method& updateBookInfo = methOpt.value();
		SmartAny retObj = updateBookInfo(bookObj).invoke();

		ASSERT_FALSE(retObj.get().has_value());
		EXPECT_TRUE(book::test_method_updateBookInfo(bookObj.get()));
	}


	TEST(ClassBookMethodOverload, args_string_double_charPtr)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
		ASSERT_TRUE(methOpt.has_value());

		SmartAny bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj.get().has_value());

		string author = book::AUTHOR;
		const Method& updateBookInfo = methOpt.value();

		SmartAny retObj = updateBookInfo(bookObj).invoke(author, book::PRICE, book::TITLE);
		ASSERT_FALSE(retObj.get().has_value());

		const bool isSuccess = book::test_method_updateBookInfo<string, double, const char*>(bookObj.get());
		EXPECT_TRUE(isSuccess);
	}


	TEST(ClassBookMethodOverload, args_charPtr_double_string)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
		ASSERT_TRUE(methOpt.has_value());

		SmartAny bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj.get().has_value());

		string author = book::AUTHOR;
		const Method& updateBookInfo = methOpt.value();

		SmartAny retObj = updateBookInfo(bookObj).invoke(book::TITLE, book::PRICE, author);
		ASSERT_FALSE(retObj.get().has_value());

		const bool isSuccess = book::test_method_updateBookInfo<const char* , double, string>(bookObj.get());
		EXPECT_TRUE(isSuccess);
	}
}