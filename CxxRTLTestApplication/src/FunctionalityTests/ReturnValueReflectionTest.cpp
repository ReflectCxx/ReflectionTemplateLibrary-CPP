#include <gtest/gtest.h>

#include "MyReflection.h"
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
			}
		}
	}
}