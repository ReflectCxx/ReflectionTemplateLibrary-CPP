
#include <algorithm>

#include "StringMute.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

//---------------------------StrMute--------------------------------

std::string StrMute::reverseString()
{
	return std::string(struct_) + REV_STR_VOID_RET + SUFFIX_void;
}


std::string StrMute::reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_const_char_ptr;
}


std::string StrMute::reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string;
}


std::string StrMute::reverseString(std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_lvref;
}


std::string StrMute::reverseString(std::string&& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_rvref;
}


std::string StrMute::reverseString(const std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_clvref;
}


std::string StrMute::reverseString(std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_ptr;
}


std::string StrMute::reverseString(const std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_cptr;
}


std::string StrMute::revStrConstRefArg(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref;
}


std::string StrMute::revStrRValueRefArg(std::string_view&& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_rvref;
}


std::string StrMute::revStrNonConstRefArg(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref;
}


std::string StrMute::revStrOverloadValCRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view;
}


std::string StrMute::revStrOverloadValCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref;
}


std::string StrMute::revStrOverloadValRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view;
}


std::string StrMute::revStrOverloadValRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref;
}


std::string StrMute::revStrOverloadRefAndCRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref;
}


std::string StrMute::revStrOverloadRefAndCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref;
}