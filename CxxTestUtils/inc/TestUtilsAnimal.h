#pragma once

#include <any>
#include <string>
/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Animal" objects states/returns without exposing the actual type "Animal".
*/
namespace test_utils
{
	struct animal
	{
		static constexpr const int AGE = 0.0;
		static constexpr const float WEIGHT = 0.0;
		static constexpr const bool IS_MAMMAL = false;
		static constexpr const char* NAME = "Orangutan";

		static constexpr const char* class_ = "Animal";
		static constexpr const char* str_setAnimalName = "setAnimalName";

		static const bool assert_zero_instance_count();

		static const bool test_method_setAnimalName_rvalue_args(const std::any& pInstance);
	};
}