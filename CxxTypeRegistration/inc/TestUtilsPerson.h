#pragma once

#include <any>
#include <string>
/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Person" objects states/returns without exposing the actual type "Person".
*/
namespace test_utils
{
	struct person
	{
		static constexpr const char* FIRST_NAME = "Sherlock";
		static constexpr const char* LAST_NAME = "Holmes";
		static constexpr const char* ADDRESS = "221B Baker Street.";

		static constexpr const char* class_ = "Person";
		static constexpr const char* str_updateAddress = "updateAddress";
		static constexpr const char* str_updateLastName = "updateLastName";

		static const bool assert_zero_instance_count();

		static const bool test_method_updateAddress(const std::any& pInstance);

		static const bool test_method_updateLastName(const std::any& pInstance);

		static const bool test_method_updateAddress_const(const std::any& pInstance);

		static const bool test_method_updateLastName_const(const std::any& pInstance);
	};
}