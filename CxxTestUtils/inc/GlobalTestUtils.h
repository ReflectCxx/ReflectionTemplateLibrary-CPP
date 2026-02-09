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

	static constexpr const char* STRA = "ReflectC++";
	static constexpr const char* STRA_REVERSE = "++CtcelfeR";

	static constexpr const char* STRB = "cxxReflection";
	static constexpr const char* STRB_REVERSE = "noitcelfeRxxc";

	static constexpr const char* str_reverseString = "reverseString"; 
	static constexpr const char* str_revStrConstRefArg = "revStrConstRefArg";
	static constexpr const char* str_revStrRValueRefArg = "revStrRValueRefArg";
	static constexpr const char* str_revStrNonConstRefArg = "revStrNonConstRefArg";
	static constexpr const char* str_revStrOverloadValRef = "revStrOverloadValRef";
	static constexpr const char* str_revStrOverloadValCRef = "revStrOverloadValCRef";
	static constexpr const char* str_revStrOverloadValRefAndCRef = "revStrOverloadRefAndCRef";

	static constexpr const char* str_getComplexNumAsString = "getComplexNumAsString";

	static constexpr const char* str_setReal = "complex::setReal";
	static constexpr const char* str_setImaginary = "complex::setImaginary";
	static constexpr const char* str_getMagnitude = "complex::getMagnitude";

	static const char* SUFFIX_void = "_void";
	static const char* SUFFIX_ctor = "_ctor";
	static const char* SUFFIX_const = "_const";
	static const char* SUFFIX_static = "_static";
	static const char* SUFFIX_const_char_ptr = "_const_char_*";

	static const char* SUFFIX_std_string = "_std::string";

	static const char* SUFFIX_std_string_ptr = "_std::string*";
	static const char* SUFFIX_std_string_cptr = "_const_std::string*";

	static const char* SUFFIX_std_string_lvref = "_std::string&";
	static const char* SUFFIX_std_string_clvref = "_const_std::string&";

	static const char* SUFFIX_std_string_rvref = "_std::string&&";

	static const char* REV_STR_VOID_RET = "func_reverseString(void)->[return_str]";

	static const char* SUFFIX_std_string_view = "_std::string_view";
	static const char* SUFFIX_std_string_view_lvref = "_std::string_view&";
	static const char* SUFFIX_std_string_view_rvref = "_std::string_view&&";
	static const char* SUFFIX_std_string_view_clvref = "_const_std::string_view&";
}