#include <gtest/gtest.h>

#include "Reflection.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests {

	TEST(ClassBookMethod, args_void)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> recOpt = cxxMirror.getRecord("Book");
		ASSERT_TRUE(recOpt.has_value());

		const Record& classBook = recOpt.value();

		optional<Method> methOpt = classBook.getMethod("getPublishedOn");
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
}