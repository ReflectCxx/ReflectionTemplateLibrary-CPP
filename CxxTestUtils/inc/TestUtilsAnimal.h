#pragma once
/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Animal" objects states/returns without exposing the actual type "Animal".
*/

#include <string>

namespace rtl::access {
	class RObject;
}


namespace test_utils
{
	struct animal
	{
		static constexpr const int AGE = 0.0;
		static constexpr const float WEIGHT = 0.0;
		static constexpr const bool IS_MAMMAL = false;
		static constexpr const char* NAME = "Orangutan";
		static constexpr const char* FAMILY_NAME = "Great Ape";
		static constexpr const char* ZOO_KEEPER = "Donald McAdams";

		static constexpr const char* class_ = "Animal";
		static constexpr const char* str_updateZooKeeper = "updateZooKeeper";
		static constexpr const char* str_setAnimalName = "setAnimalName";
		static constexpr const char* str_setFamilyName = "setFamilyName";
		static constexpr const char* str_getFamilyName = "getFamilyName";

		static const bool assert_zero_instance_count();

		static const bool test_method_setAnimalName_rvalue_args(const rtl::access::RObject& pInstance);

		static const bool test_method_setAnimalName_const_lvalue_ref_args(const rtl::access::RObject& pInstance);

		static const bool test_method_setAnimalName_non_const_lvalue_ref_args(const rtl::access::RObject& pInstance);

		template<class ..._signature>
		static const bool test_method_updateZooKeeper(const std::string& pZooKeeper);
	};
}