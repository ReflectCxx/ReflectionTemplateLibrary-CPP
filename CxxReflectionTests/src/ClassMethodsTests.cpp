#include <gtest/gtest.h>

#include "Reflection.h"

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

		std::unique_ptr<RObject> bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj != nullptr);

		const char* authorStr = book::AUTHOR;
		const Method& setAuthor = methOpt.value();

		std::unique_ptr<RObject> retObj = setAuthor(bookObj).invoke(authorStr);
		ASSERT_TRUE(retObj == nullptr);

		EXPECT_FALSE(book::test_method_setAuthor(bookObj));
	}


	TEST(ClassBookMethod, args_void)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_getPublishedOn);
		ASSERT_TRUE(methOpt.has_value());

		std::unique_ptr<RObject> bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj != nullptr);

		const Method& getPublishedOn = methOpt.value();

		std::unique_ptr<RObject> retObj = getPublishedOn(bookObj).invoke();
		ASSERT_TRUE(retObj != nullptr);

		optional<string> retOp = retObj->get<string>();
		ASSERT_TRUE(retOp.has_value());

		const string& retStr = retOp.value();
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

		std::unique_ptr<RObject> bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj != nullptr);

		std::string authorStr = book::AUTHOR;
		const Method& setAuthor = methOpt.value();

		std::unique_ptr<RObject> retObj = setAuthor(bookObj).invoke(authorStr);
		ASSERT_TRUE(retObj == nullptr);

		EXPECT_TRUE(book::test_method_setAuthor(bookObj));
	}


	TEST(ClassBookMethodOverload, args_void)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
		ASSERT_TRUE(methOpt.has_value());

		std::unique_ptr<RObject> bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj != nullptr);

		const Method& updateBookInfo = methOpt.value();

		std::unique_ptr<RObject> retObj = updateBookInfo(bookObj).invoke();
		ASSERT_TRUE(retObj == nullptr);
		EXPECT_TRUE(book::test_method_updateBookInfo(bookObj));
	}


	TEST(ClassBookMethodOverload, args_string_double_charPtr)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
		ASSERT_TRUE(methOpt.has_value());

		std::unique_ptr<RObject> bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj != nullptr);

		string author = book::AUTHOR;
		const Method& updateBookInfo = methOpt.value();

		std::unique_ptr<RObject> retObj = updateBookInfo(bookObj).invoke(author, book::PRICE, book::TITLE);
		ASSERT_TRUE(retObj == nullptr);

		const bool isSuccess = book::test_method_updateBookInfo<string, double, const char*>(bookObj);
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

		std::unique_ptr<RObject> bookObj = classBook.newInstance();
		ASSERT_TRUE(bookObj != nullptr);

		string author = book::AUTHOR;
		const Method& updateBookInfo = methOpt.value();

		std::unique_ptr<RObject> retObj = updateBookInfo(bookObj).invoke(book::TITLE, book::PRICE, author);
		ASSERT_TRUE(retObj == nullptr);

		const bool isSuccess = book::test_method_updateBookInfo<const char* , double, string>(bookObj);
		EXPECT_TRUE(isSuccess);
	}
}