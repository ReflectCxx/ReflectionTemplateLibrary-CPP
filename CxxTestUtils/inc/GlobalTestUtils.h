#pragma once

#include <string>

/*
TestUtils provide the interface to test/compare reflected type objects with actual objects (retrived/created using
strict Types) without exposing the actual type objects to "CxxReflectionTests" project.

Provides interface for Testing/Comparing the global functions & types (may or not be in some namespace) without exposing their actual implementation.
*/
namespace test_utils {

	extern const char* REV_STR_VOID_RET;

	static constexpr double g_real = 3.92;
	static constexpr double g_imaginary = 9.27;

	static constexpr const char* STRA = "ReflectC++";
	static constexpr const char* STRA_REVERSE = "++CtcelfeR";

	static constexpr const char* STRB = "cxxReflection";
	static constexpr const char* STRB_REVERSE = "noitcelfeRxxc";

	static constexpr const char* str_reverseString = "reverseString";
	static constexpr const char* str_getComplexNumAsString = "getComplexNumAsString";

	static constexpr const char* str_complex = "complex";
	static constexpr const char* str_setReal = "setReal";
	static constexpr const char* str_setImaginary = "setImaginary";
	static constexpr const char* str_getMagnitude = "getMagnitude";

	const std::size_t getRecordIdFor(const std::string& pRecordName);

	struct id {

		static std::size_t date;
		static std::size_t book;
		static std::size_t event;
		static std::size_t animal;
		static std::size_t person;
		static std::size_t library;
		static std::size_t calender;
	};
}