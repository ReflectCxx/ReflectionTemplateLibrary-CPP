#pragma once

#include <string>

/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the global functions & types (may or not be in some namespace) without exposing their actual implementation.
*/
namespace test_utils {

	static constexpr double g_real = 3.92;
	static constexpr double g_imaginary = 9.27;

	inline constexpr std::string_view STRA = "ReflectC++";
	inline constexpr std::string_view STRA_REVERSE = "++CtcelfeR";

	inline constexpr std::string_view STRB = "cxxReflection";
	inline constexpr std::string_view STRB_REVERSE = "noitcelfeRxxc";

	inline constexpr std::string_view str_reverseString = "reverseString"; 
	inline constexpr std::string_view str_revStrConstRefArg = "revStrConstRefArg";
	inline constexpr std::string_view str_revStrRValueRefArg = "revStrRValueRefArg";
	inline constexpr std::string_view str_revStrNonConstRefArg = "revStrNonConstRefArg";
	inline constexpr std::string_view str_revStrOverloadValRef = "revStrOverloadValRef";
	inline constexpr std::string_view str_revStrOverloadValCRef = "revStrOverloadValCRef";

	inline constexpr std::string_view SUFFIX_void = "_void";
	inline constexpr std::string_view SUFFIX_ctor = "_ctor";
	inline constexpr std::string_view SUFFIX_const = "_const";
	inline constexpr std::string_view SUFFIX_static = "_static";
	inline constexpr std::string_view SUFFIX_const_char_ptr = "_const_char_*";

	inline constexpr std::string_view SUFFIX_std_string = "_std::string";

	inline constexpr std::string_view SUFFIX_std_string_ptr = "_std::string*";
	inline constexpr std::string_view SUFFIX_std_string_cptr = "_const_std::string*";

	inline constexpr std::string_view SUFFIX_std_string_lvref = "_std::string&";
	inline constexpr std::string_view SUFFIX_std_string_clvref = "_const_std::string&";

	inline constexpr std::string_view SUFFIX_std_string_rvref = "_std::string&&";

	inline constexpr std::string_view REV_STR_VOID_RET = "func_reverseString(void)->[return_str]";

	inline constexpr std::string_view SUFFIX_std_string_view = "_std::string_view";
	inline constexpr std::string_view SUFFIX_std_string_view_lvref = "_std::string_view&";
	inline constexpr std::string_view SUFFIX_std_string_view_rvref = "_std::string_view&&";
	inline constexpr std::string_view SUFFIX_std_string_view_clvref = "_const_std::string_view&";
}