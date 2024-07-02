#pragma once

#include <any>

/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Date" objects states/returns without exposing the actual type "Date".
*/
namespace test_utils
{
	struct date
	{
		static constexpr const unsigned DAY = 1;
		static constexpr const unsigned MONTH = 1;
		static constexpr const unsigned YEAR = 2000;
		static constexpr const char* DATE_STR = "23/12/2024";

		static constexpr const char* ns = "nsdate";
		static constexpr const char* struct_ = "Date";
		
		static const bool assert_zero_instance_count();

		template<class ..._argsType>
		static const bool test_dynamic_alloc_instance_ctor(const std::any& pInstance);
	};
}