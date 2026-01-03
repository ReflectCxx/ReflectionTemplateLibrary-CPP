
#include <algorithm>

#include "StringConst.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

//---------------------------StrConst--------------------------------

std::string StrConst::reverseString() const
{
	return std::string(struct_) + REV_STR_VOID_RET + SUFFIX_void + SUFFIX_const;
}


std::string StrConst::reverseString(const char* pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_const_char_ptr + SUFFIX_const;
}


std::string StrConst::reverseString(std::string pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string + SUFFIX_const;
}


std::string StrConst::reverseString(std::string& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_lvref + SUFFIX_const;
}


std::string StrConst::reverseString(std::string&& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_rvref + SUFFIX_const;
}


std::string StrConst::reverseString(const std::string& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_clvref + SUFFIX_const;
}


std::string StrConst::reverseString(std::string* pStr) const
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_ptr + SUFFIX_const;
}


std::string StrConst::reverseString(const std::string* pStr) const
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_cptr + SUFFIX_const;
}


std::string StrConst::revStrConstRefArg(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref + SUFFIX_const;
}


std::string StrConst::revStrRValueRefArg(std::string_view&& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_rvref + SUFFIX_const;
}


std::string StrConst::revStrNonConstRefArg(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref + SUFFIX_const;
}


std::string StrConst::revStrOverloadValCRef(std::string_view pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view + SUFFIX_const;
}


std::string StrConst::revStrOverloadValCRef(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref + SUFFIX_const;
}


std::string StrConst::revStrOverloadValRef(std::string_view pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view + SUFFIX_const;
}


std::string StrConst::revStrOverloadValRef(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref + SUFFIX_const;
}


std::string StrConst::revStrOverloadRefAndCRef(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref + SUFFIX_const;
}


std::string StrConst::revStrOverloadRefAndCRef(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref + SUFFIX_const;
}