#pragma once

#include <any>

/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Date" objects states/returns without exposing the actual type "Date".
*/
namespace test_utils
{
	struct calender 
	{
		static constexpr const char* ns = "nsdate";
		static constexpr const char* struct_ = "Calender";
		static constexpr const char* str_create = "create";
		static const bool assert_zero_instance_count();
		static const std::size_t get_instance_count();
	};

	struct date
	{
		static constexpr const unsigned DAY = 1;
		static constexpr const unsigned MONTH = 1;
		static constexpr const unsigned YEAR = 2000;
		static constexpr const char* DATE_STR0 = "23/12/2024";
		static constexpr const char* DATE_STR1 = "04/05/2025";

		static constexpr const char* ns = "nsdate";
		static constexpr const char* struct_ = "Date";
		static constexpr const char* str_updateDate = "updateDate";
		static constexpr const char* str_getAsString = "getAsString";
		static constexpr const char* str_getCalenderPtr = "getCalenderPtr";
		static constexpr const char* str_getCalenderRef = "getCalenderRef";

		static const std::size_t get_date_instance_count();

		static const bool test_if_obejcts_are_equal(const std::any& pInstance0, const std::any& pInstance1, bool pIsOnHeap);

		template<class ..._argsType>
		static const bool test_dynamic_alloc_instance_ctor(const std::any& pInstance, bool pOnHeap);
	};
}