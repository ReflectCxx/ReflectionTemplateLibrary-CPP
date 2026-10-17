
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
	:StrWrap(std::string(struct_).append(SUFFIX_ctor))
{ }

StrWrapA::StrWrapA(std::string_view pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_std_string_view).append(SUFFIX_ctor))
{ }

StrWrapA::StrWrapA(std::string& pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_std_string_lvref).append(SUFFIX_ctor))
{ }

StrWrapA::StrWrapA(const std::string& pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_std_string_clvref).append(SUFFIX_ctor))
{ }

StrWrapA::StrWrapA(std::string&& pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_std_string_rvref).append(SUFFIX_ctor))
{ }

StrWrapA::StrWrapA(const char* pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_const_char_ptr).append(SUFFIX_ctor))
{ }

StrWrapB::StrWrapB(const std::string& pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_std_string_clvref).append(SUFFIX_ctor))
{ }

StrWrapB::StrWrapB(std::string& pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_std_string_lvref).append(SUFFIX_ctor))
{ }

StrWrapC::StrWrapC(std::string& pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_std_string_lvref).append(SUFFIX_ctor))
{ }

StrWrapD::StrWrapD(const std::string& pStr)
	:StrWrap(std::string(struct_).append(pStr).append(SUFFIX_std_string_clvref).append(SUFFIX_ctor))
{ }