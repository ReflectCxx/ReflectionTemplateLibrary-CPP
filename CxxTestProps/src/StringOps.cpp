
#include <algorithm>

#include "StringOps.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

std::string reverseString()
{
	return std::string(REV_STR_VOID_RET) + SUFFIX_void;
}


std::string reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_const_char_ptr;
}


std::string reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string;
}


std::string reverseString(std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_lvref;
}


std::string reverseString(std::string&& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_rvref;
}


std::string reverseString(const std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_clvref;
}


std::string reverseString(std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_ptr;
}


std::string reverseString(const std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_cptr;
}


std::string revStrConstRefArg(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref;
}


std::string revStrRValueRefArg(std::string_view&& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_rvref;
}


std::string revStrNonConstRefArg(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref;
}


std::string revStrOverloadValCRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view;
}


std::string revStrOverloadValCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref;
}


std::string revStrOverloadValRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view;
}


std::string revStrOverloadValRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref;
}


std::string revStrOverloadRefAndCRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref;
}


std::string revStrOverloadRefAndCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref;
}