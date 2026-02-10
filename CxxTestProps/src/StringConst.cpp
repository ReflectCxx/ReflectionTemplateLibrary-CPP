
#include <algorithm>

#include "StringConst.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

//---------------------------StrConst--------------------------------

std::string StrConst::reverseString() const
{
	return std::string(struct_).append(REV_STR_VOID_RET).append(SUFFIX_void).append(SUFFIX_const);
}


std::string StrConst::reverseString(const char* pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_const_char_ptr).append(SUFFIX_const);
}


std::string StrConst::reverseString(std::string pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string).append(SUFFIX_const);
}


std::string StrConst::reverseString(std::string& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_lvref).append(SUFFIX_const);
}


std::string StrConst::reverseString(std::string&& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_rvref).append(SUFFIX_const);
}


std::string StrConst::reverseString(const std::string& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_clvref).append(SUFFIX_const);
}


std::string StrConst::reverseString(std::string* pStr) const
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_ptr).append(SUFFIX_const);
}


std::string StrConst::reverseString(const std::string* pStr) const
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_cptr).append(SUFFIX_const);
}


std::string StrConst::revStrConstRefArg(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_clvref).append(SUFFIX_const);
}


std::string StrConst::revStrRValueRefArg(std::string_view&& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_rvref).append(SUFFIX_const);
}


std::string StrConst::revStrNonConstRefArg(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_lvref).append(SUFFIX_const);
}


std::string StrConst::revStrOverloadValCRef(std::string_view pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view).append(SUFFIX_const);
}


std::string StrConst::revStrOverloadValCRef(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_clvref).append(SUFFIX_const);
}


std::string StrConst::revStrOverloadValRef(std::string_view pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view).append(SUFFIX_const);
}


std::string StrConst::revStrOverloadValRef(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_lvref).append(SUFFIX_const);
}


std::string StrConst::revStrOverloadRefAndCRef(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_lvref).append(SUFFIX_const);
}


std::string StrConst::revStrOverloadRefAndCRef(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_clvref).append(SUFFIX_const);
}