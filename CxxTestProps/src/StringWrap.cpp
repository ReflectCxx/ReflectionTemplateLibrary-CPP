
#include "StringWrap.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

const std::string& StrWrap::sstr() const {
	return m_str;
}

StrWrap::StrWrap()
	:m_str(std::string(DEFAULT_str) + SUFFIX_ctor)
{ }

StrWrap::StrWrap(std::string_view pStr)
	:m_str(std::string(pStr) + SUFFIX_std_string_view + SUFFIX_ctor)
{ }

StrWrap::StrWrap(std::string& pStr)
	:m_str(pStr + SUFFIX_std_string_lvref + SUFFIX_ctor)
{ }

StrWrap::StrWrap(const std::string& pStr)
	:m_str(pStr + SUFFIX_std_string_clvref + SUFFIX_ctor)
{ }

StrWrap::StrWrap(std::string&& pStr)
	:m_str(pStr + SUFFIX_std_string_rvref + SUFFIX_ctor)
{ }

StrWrap::StrWrap(const char* pStr)
	:m_str(std::string(pStr) + SUFFIX_const_char_ptr + SUFFIX_ctor)
{ }