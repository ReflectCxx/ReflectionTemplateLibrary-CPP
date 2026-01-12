#pragma once
/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the class "Person" objects states/returns without exposing the actual type "Person".
*/

#include <string>

namespace rtl {
	class RObject;
}

namespace test_utils
{
	struct person
	{
		static constexpr const std::size_t AGE = 34;
		static constexpr const char* FIRST_NAME = "Sherlock";
		static constexpr const char* LAST_NAME = "Holmes";
		static constexpr const char* ADDRESS = "221B Baker Street.";
		static constexpr const char* OCCUPATION = "Private Detective.";

		static constexpr const char* class_ = "Person";
		static constexpr const char* str_createPtr = "createPtr";
		static constexpr const char* str_getProfile = "getProfile";
		static constexpr const char* str_createConst = "createConst";
		static constexpr const char* str_getDefaults = "getDefaults";
		static constexpr const char* str_getFirstName = "getFirstName";
		static constexpr const char* str_updateAddress = "updateAddress";
		static constexpr const char* str_updateLastName = "updateLastName";

		static const bool assert_zero_instance_count();

		static const std::string get_str_returned_on_call_getDefaults();

		static const bool delete_unmanaged_person_instance_created_via_createPtr(const rtl::RObject& pInstance);

		template<class ...signature_t>
		static const std::string get_str_returned_on_call_getProfile(const bool pNoAddress = false);

		static const bool test_method_updateLastName_const(const rtl::RObject& pInstance);

		template<class ...signature_t>
		static const bool test_method_updateAddress(const rtl::RObject& pInstance);

		template<class ...signature_t>
		static const bool test_method_updateAddress_const(const rtl::RObject& pInstance);

		static const bool test_copy_constructor_overload_src_const_obj(const rtl::RObject& pInstance);

		static const bool test_copy_constructor_overload_src_non_const_obj(const rtl::RObject& pInstance);
	};
}