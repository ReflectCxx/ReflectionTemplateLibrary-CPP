#pragma once
/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Animal" objects states/returns without exposing the actual type "Animal".
*/

#include <string>

namespace rtl {
	class RObject;
}


namespace test_utils
{
	struct animal
	{
		static constexpr const int AGE = 0.0;
		static constexpr const float WEIGHT = 0.0;
		static constexpr const bool IS_MAMMAL = false;
		static constexpr std::string_view NAME = "Orangutan";
		static constexpr std::string_view FAMILY_NAME = "Great Ape";
		static constexpr std::string_view ZOO_KEEPER = "Donald McAdams";

		static constexpr std::string_view class_ = "Animal";
		static constexpr std::string_view str_updateZooKeeper = "updateZooKeeper";
		static constexpr std::string_view str_setAnimalName = "setAnimalName";
		static constexpr std::string_view str_setFamilyName = "setFamilyName";
		static constexpr std::string_view str_getFamilyName = "getFamilyName";

		static const bool assert_zero_instance_count();

		static const bool test_method_setAnimalName_rvalue_args(const rtl::RObject& pInstance);

		static const bool test_method_setAnimalName_const_lvalue_ref_args(const rtl::RObject& pInstance);

		static const bool test_method_const_setAnimalName_const_lvalue_ref_args(const rtl::RObject& pInstance);

		static const bool test_method_setAnimalName_non_const_lvalue_ref_args(const rtl::RObject& pInstance);

		template<class ...signature_t>
		static const bool test_method_updateZooKeeper(const std::string& pZooKeeper);
	};
}