#include <gtest/gtest.h>

#include "TestUtils.h"
#include "Reflection.h"

using namespace std;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests {

	TEST(ConstructorTest, DefaultCtor)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord("test_project", "Date");
		EXPECT_TRUE(record.has_value());

		const Record& classDate = record.value();
		unique_ptr<RObject> instance = classDate.newInstance();

		EXPECT_TRUE(instance != nullptr);
		EXPECT_TRUE(date::testNewInstanceDefaultCtor(instance));
	}


	TEST(ConstructorTest, OverloadedCtorString)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord("test_project", "Date");
		EXPECT_TRUE(record.has_value());

		const Record& classDate = record.value();
		const string& dateStr = date::DATE_STR;
		unique_ptr<RObject> instance = classDate.newInstance(dateStr);

		EXPECT_TRUE(instance != nullptr);
		EXPECT_TRUE(date::testNewInstanceCtorString(instance));
	}


	TEST(ConstructorTest, OverloadedCtorUnsignedInt)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord("test_project", "Date");
		EXPECT_TRUE(record.has_value());

		const Record& classDate = record.value();
		unique_ptr<RObject> instance = classDate.newInstance(date::day, date::month, date::year);

		EXPECT_TRUE(instance != nullptr);
		EXPECT_TRUE(date::testNewInstanceCtorUnsignedInt(instance));
	}


	TEST(DestructorTest, NonVirtual)
	{
		EXPECT_TRUE(date::assertZeroInstanceCount());

		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> record = cxxMirror.getRecord("test_project", "Date");
		EXPECT_TRUE(record.has_value());
		{
			const Record& classDate = record.value();
			unique_ptr<RObject> instance = classDate.newInstance();
		}
		EXPECT_TRUE(date::assertZeroInstanceCount());
	}
}