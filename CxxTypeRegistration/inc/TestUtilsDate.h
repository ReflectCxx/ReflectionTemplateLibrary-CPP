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
		static constexpr const unsigned day = 1;
		static constexpr const unsigned month = 1;
		static constexpr const unsigned year = 2000;
		static constexpr const char* ns = "nsdate";
		static constexpr const char* struct_ = "Date";
		static constexpr const char* DATE_STR = "23/12/2024";
		
		static const bool assert_zero_instance_count();

		template<class ..._argsType>
		static const bool test_heap_instance_ctor(const std::any& pInstance);

		template<class ..._argsType>
		static const bool test_stack_instance_ctor(const std::any& pInstance);
	};
}