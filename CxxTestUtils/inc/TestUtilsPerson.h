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
		static constexpr std::string_view FIRST_NAME = "Sherlock";
		static constexpr std::string_view LAST_NAME = "Holmes";
		static constexpr std::string_view ADDRESS = "221B Baker Street.";
		static constexpr std::string_view OCCUPATION = "Private Detective.";

		static constexpr std::string_view class_ = "Person";
		static constexpr std::string_view str_createPtr = "createPtr";
		static constexpr std::string_view str_getProfile = "getProfile";
		static constexpr std::string_view str_createConst = "createConst";
		static constexpr std::string_view str_getDefaults = "getDefaults";
		static constexpr std::string_view str_getFirstName = "getFirstName";
		static constexpr std::string_view str_updateAddress = "updateAddress";
		static constexpr std::string_view str_updateLastName = "updateLastName";

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
	};
}