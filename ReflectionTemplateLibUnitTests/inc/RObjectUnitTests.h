#pragma once

#include <string>

namespace rtl
{
	namespace unit_test
	{
		static const std::string STRING_STD_STRING = "string_type: std::string.";
		static constexpr const char* STRING_CONST_CHAR_POINTER = "string_type: const_char_*.";

		static char STRING_CHAR_ARRAY[] = "string_type: const_char_array.";
		static constexpr const char STRING_CONST_CHAR_ARRAY[] = "string_type: const_char_array.";
	}
}