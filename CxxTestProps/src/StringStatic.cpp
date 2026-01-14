
#include <algorithm>

#include "StringStatic.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

//---------------------------StrStatic--------------------------------

std::string StrStatic::reverseString()
{
	return std::string(struct_) + (REV_STR_VOID_RET) + SUFFIX_void + SUFFIX_static;
}


std::string StrStatic::reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_const_char_ptr + SUFFIX_static;
}


std::string StrStatic::reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string + SUFFIX_static;
}


std::string StrStatic::reverseString(std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_lvref + SUFFIX_static;
}


std::string StrStatic::reverseString(std::string&& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_rvref + SUFFIX_static;
}


std::string StrStatic::reverseString(const std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_clvref + SUFFIX_static;
}


std::string StrStatic::reverseString(std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_ptr + SUFFIX_static;
}


std::string StrStatic::reverseString(const std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_cptr + SUFFIX_static;
}


std::string StrStatic::revStrConstRefArg(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref + SUFFIX_static;
}


std::string StrStatic::revStrRValueRefArg(std::string_view&& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_rvref + SUFFIX_static;
}


std::string StrStatic::revStrNonConstRefArg(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref + SUFFIX_static;
}


std::string StrStatic::revStrOverloadValCRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view + SUFFIX_static;
}


std::string StrStatic::revStrOverloadValCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref + SUFFIX_static;
}


std::string StrStatic::revStrOverloadValRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view + SUFFIX_static;
}


std::string StrStatic::revStrOverloadValRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref + SUFFIX_static;
}


std::string StrStatic::revStrOverloadRefAndCRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_lvref + SUFFIX_static;
}


std::string StrStatic::revStrOverloadRefAndCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_) + retStr + SUFFIX_std_string_view_clvref + SUFFIX_static;
}