
#include <algorithm>

#include "StringStatic.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

//---------------------------StrStatic--------------------------------

std::string StrStatic::reverseString()
{
	return std::string(struct_).append((REV_STR_VOID_RET)).append(SUFFIX_void).append(SUFFIX_static);
}


std::string StrStatic::reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_const_char_ptr).append(SUFFIX_static);
}


std::string StrStatic::reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string).append(SUFFIX_static);
}


std::string StrStatic::reverseString(std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_lvref).append(SUFFIX_static);
}


std::string StrStatic::reverseString(std::string&& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_rvref).append(SUFFIX_static);
}


std::string StrStatic::reverseString(const std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_clvref).append(SUFFIX_static);
}


std::string StrStatic::reverseString(std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_ptr).append(SUFFIX_static);
}


std::string StrStatic::reverseString(const std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_cptr).append(SUFFIX_static);
}


std::string StrStatic::revStrConstRefArg(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_clvref).append(SUFFIX_static);
}


std::string StrStatic::revStrRValueRefArg(std::string_view&& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_rvref).append(SUFFIX_static);
}


std::string StrStatic::revStrNonConstRefArg(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_lvref).append(SUFFIX_static);
}


std::string StrStatic::revStrOverloadValCRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view).append(SUFFIX_static);
}


std::string StrStatic::revStrOverloadValCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_clvref).append(SUFFIX_static);
}


std::string StrStatic::revStrOverloadValRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view).append(SUFFIX_static);
}


std::string StrStatic::revStrOverloadValRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_lvref).append(SUFFIX_static);
}


std::string StrStatic::revStrOverloadRefAndCRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_lvref).append(SUFFIX_static);
}


std::string StrStatic::revStrOverloadRefAndCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return std::string(struct_).append(retStr).append(SUFFIX_std_string_view_clvref).append(SUFFIX_static);
}