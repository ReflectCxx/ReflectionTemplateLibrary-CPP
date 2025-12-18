
#include "StringWrap.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

const std::string& StrWrap::sstr() const {
	return m_str;
}

StrWrap::StrWrap(const std::string& pStr)
	:m_str(pStr)
{ }

StrWrapA::StrWrapA()
	:StrWrap(std::string(struct_) + SUFFIX_ctor)
{ }

StrWrapA::StrWrapA(std::string_view pStr)
	:StrWrap(std::string(struct_) + std::string(pStr) + SUFFIX_std_string_view + SUFFIX_ctor)
{ }

StrWrapA::StrWrapA(std::string& pStr)
	:StrWrap(std::string(struct_) + pStr + SUFFIX_std_string_lvref + SUFFIX_ctor)
{ }

StrWrapA::StrWrapA(const std::string& pStr)
	:StrWrap(std::string(struct_) + pStr + SUFFIX_std_string_clvref + SUFFIX_ctor)
{ }

StrWrapA::StrWrapA(std::string&& pStr)
	:StrWrap(std::string(struct_) + pStr + SUFFIX_std_string_rvref + SUFFIX_ctor)
{ }

StrWrapA::StrWrapA(const char* pStr)
	:StrWrap(std::string(struct_) + std::string(pStr) + SUFFIX_const_char_ptr + SUFFIX_ctor)
{ }

StrWrapB::StrWrapB(const std::string& pStr)
	:StrWrap(std::string(struct_) + pStr + SUFFIX_std_string_clvref + SUFFIX_ctor)
{ }

StrWrapB::StrWrapB(std::string& pStr)
	:StrWrap(std::string(struct_) + pStr + SUFFIX_std_string_lvref + SUFFIX_ctor)
{ }

StrWrapC::StrWrapC(std::string& pStr)
	:StrWrap(std::string(struct_) + pStr + SUFFIX_std_string_lvref + SUFFIX_ctor)
{ }

StrWrapD::StrWrapD(const std::string& pStr)
	:StrWrap(std::string(struct_) + pStr + SUFFIX_std_string_clvref + SUFFIX_ctor)
{ }