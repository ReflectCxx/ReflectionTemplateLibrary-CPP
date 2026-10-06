#pragma once

/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Date" objects states/returns without exposing the actual type "Date".
*/

namespace rtl {
	class RObject;
}

namespace test_utils
{
	struct event
	{
		static const bool assert_zero_instance_count();
		static const std::size_t get_instance_count();
	};

	struct calender
	{
		static void reset_move_ops_counter();
		static const bool assert_zero_instance_count();
		static const std::size_t get_instance_count();
		static const std::size_t get_move_ops_count();
	};

	struct date
	{
		static constexpr const unsigned DAY = 1;
		static constexpr const unsigned MONTH = 1;
		static constexpr const unsigned YEAR = 2000;
		static constexpr std::string_view DATE_STR0 = "23/12/2024";
		static constexpr std::string_view DATE_STR1 = "04/05/2025";

		static const std::size_t get_instance_count();

		static const bool test_if_obejcts_are_equal(const rtl::RObject& pInstance0, const rtl::RObject& pInstance1);

		template<class ..._argsType>
		static const bool test_dynamic_alloc_instance_ctor(const rtl::RObject& pInstance);
	};
}