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
		optional<Method> badMethod = classBook.getMethod("no_method");
		EXPECT_FALSE(badMethod.has_value());
	}


	TEST(ClassBookMethod, wrong_args)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_setAuthor);
			ASSERT_TRUE(methOpt.has_value());

			RStatus retIns = classBook.instance();
			ASSERT_TRUE(retIns.didCallSucceed());

			SmartAny bookObj = retIns.releaseReturn();
			ASSERT_TRUE(bookObj.getReturn().has_value());

			const char* authorStr = book::AUTHOR;
			const Method& setAuthor = methOpt.value();

			RStatus callRet = setAuthor(bookObj).invoke(authorStr);
			ASSERT_FALSE(callRet.didCallSucceed());

			SmartAny retObj = callRet.releaseReturn();

			ASSERT_FALSE(retObj.getReturn().has_value());
			EXPECT_FALSE(book::test_method_setAuthor(bookObj.getReturn()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethod, ret_string_args_void)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(methOpt.has_value());

			RStatus retIns = classBook.instance();
			ASSERT_TRUE(retIns.didCallSucceed());

			SmartAny bookObj = retIns.releaseReturn();
			ASSERT_TRUE(bookObj.getReturn().has_value());

			const Method& getPublishedOn = methOpt.value();
			RStatus callRet = getPublishedOn(bookObj).invoke();
			ASSERT_TRUE(callRet.didCallSucceed());

			SmartAny retObj = callRet.releaseReturn();
			ASSERT_TRUE(retObj.getReturn().has_value() && retObj.isOfType<string>());

			const std::string& retStr = any_cast<string>(retObj.getReturn());
			EXPECT_TRUE(book::test_method_getPublishedOn_return(retStr));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethod, ret_void_args_string)
	{
		EXPECT_TRUE(book::assert_zero_instance_count()); 
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_setAuthor);
			ASSERT_TRUE(methOpt.has_value());

			RStatus retIns = classBook.instance();
			ASSERT_TRUE(retIns.didCallSucceed());

			SmartAny bookObj = retIns.releaseReturn();
			ASSERT_TRUE(bookObj.getReturn().has_value());

			std::string authorStr = book::AUTHOR;
			const Method& setAuthor = methOpt.value();

			RStatus callRet = setAuthor(bookObj).invoke(authorStr);
			ASSERT_TRUE(callRet.didCallSucceed());

			SmartAny retObj = callRet.releaseReturn();
			ASSERT_FALSE(retObj.getReturn().has_value());

			EXPECT_TRUE(book::test_method_setAuthor(bookObj.getReturn()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethodOverload, ret_void_args_void)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			EXPECT_TRUE(book::assert_zero_instance_count());

			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(methOpt.has_value());

			RStatus retIns = classBook.instance();
			ASSERT_TRUE(retIns.didCallSucceed());

			SmartAny bookObj = retIns.releaseReturn();
			ASSERT_TRUE(bookObj.getReturn().has_value());

			const Method& updateBookInfo = methOpt.value();
			RStatus callRet = updateBookInfo(bookObj).invoke();
			ASSERT_TRUE(callRet.didCallSucceed());

			SmartAny retObj = callRet.releaseReturn();
			ASSERT_FALSE(retObj.getReturn().has_value());

			EXPECT_TRUE(book::test_method_updateBookInfo(bookObj.getReturn()));
		}
	}


	TEST(ClassBookMethodOverload, ret_void_args_string_double_charPtr)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(methOpt.has_value());

			RStatus retIns = classBook.instance();
			ASSERT_TRUE(retIns.didCallSucceed());

			SmartAny bookObj = retIns.releaseReturn();
			ASSERT_TRUE(bookObj.getReturn().has_value());

			string author = book::AUTHOR;
			const Method& updateBookInfo = methOpt.value();

			RStatus callRet = updateBookInfo(bookObj).invoke(author, book::PRICE, book::TITLE);
			ASSERT_TRUE(callRet.didCallSucceed());

			SmartAny retObj = callRet.releaseReturn();
			ASSERT_FALSE(retObj.getReturn().has_value());

			const bool isSuccess = book::test_method_updateBookInfo<string, double, const char*>(bookObj.getReturn());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}


	TEST(ClassBookMethodOverload, ret_void_args_charPtr_double_string)
	{
		EXPECT_TRUE(book::assert_zero_instance_count());
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> recOpt = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(recOpt.has_value());

			const Record& classBook = recOpt.value();

			optional<Method> methOpt = classBook.getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(methOpt.has_value());

			RStatus retIns = classBook.instance();
			ASSERT_TRUE(retIns.didCallSucceed());

			SmartAny bookObj = retIns.releaseReturn();
			ASSERT_TRUE(bookObj.getReturn().has_value());

			string author = book::AUTHOR;
			const Method& updateBookInfo = methOpt.value();

			RStatus callRet = updateBookInfo(bookObj).invoke(book::TITLE, book::PRICE, author);
			ASSERT_TRUE(callRet.didCallSucceed());

			SmartAny retObj = callRet.releaseReturn();
			ASSERT_FALSE(retObj.getReturn().has_value());

			const bool isSuccess = book::test_method_updateBookInfo<const char*, double, string>(bookObj.getReturn());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
	}
}