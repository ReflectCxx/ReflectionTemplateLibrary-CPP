#pragma once

#include <string>

namespace rtl
{
	namespace unit_test
	{
		static const std::string STR_STD_STRING = "string_type: std::string.";
		static constexpr const char* STR_CONST_CHAR_POINTER = "string_type: const_char_*.";

		static char STR_CHAR_ARRAY[] = "string_type: const_char_array.";
		static constexpr const char STR_CONST_CHAR_ARRAY[] = "string_type: const_char_array.";

		static const std::string_view STR_STD_STRING_VIEW = STR_STD_STRING;
	}
}