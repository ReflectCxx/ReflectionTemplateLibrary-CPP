#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsDate.h"
#include "TestUtilsBook.h"
#include "GlobalTestUtils.h"

using namespace rtl::access;

namespace rtl_tests 
{
	TEST(ReflecetdReturnValues, verify_typeIds_of_registered_records)
	{
		const auto& rtl_recordIdMap = MyReflection::instance().getRecordIdMap();

		for (const auto& itr0 : MyReflection::instance().getNamespaceRecordMap())
		{
			const auto& namespaceRecordMap = itr0.second;
			for (const auto& itr1 : namespaceRecordMap)
			{
				const std::string& recordName = itr1.first;
				const std::size_t recordId = test_utils::getRecordIdFor(recordName);
				const auto& itr = rtl_recordIdMap.find(recordId);

				ASSERT_TRUE(itr != rtl_recordIdMap.end());

				const Record& reflectedClass = itr->second.get();

				auto [err, robj] = reflectedClass.create<rtl::alloc::Stack>();

				if (recordName == test_utils::calender::struct_) {

					EXPECT_TRUE(err == rtl::error::ConstructorNotRegisteredInRTL);
					EXPECT_TRUE(robj.isEmpty());
				}
				else if (recordName == test_utils::library::class_) {

					EXPECT_TRUE(err == rtl::error::CopyConstructorPrivateOrDeleted);
					EXPECT_TRUE(robj.isEmpty());
				}
				else {

					EXPECT_TRUE(err == rtl::error::None);
					EXPECT_FALSE(robj.isEmpty());
					EXPECT_TRUE(robj.getTypeId() == recordId);
				}
			}
		}
	}
}