
#include <algorithm>

#include "StringOps.h"

namespace test_utils {

	const char* SUFFIX_void = "_void";
	const char* SUFFIX_const = "_const";
	const char* SUFFIX_static = "_static";
	const char* SUFFIX_const_char_ptr = "_const_char_*";

	const char* SUFFIX_std_string = "_std::string";

	const char* SUFFIX_std_string_ptr = "_std::string*";
	const char* SUFFIX_std_string_cptr = "_const_std::string*";

	const char* SUFFIX_std_string_lvref = "_std::string&";
	const char* SUFFIX_std_string_clvref = "_const_std::string&";
	
	const char* SUFFIX_std_string_rvref = "_std::string&&";

	const char* REV_STR_VOID_RET = "func_reverseString(void)->[return_str]";

	const char* SUFFIX_std_string_view = "_std::string_view";
	const char* SUFFIX_std_string_view_lvref = "_std::string_view&";
	const char* SUFFIX_std_string_view_rvref = "_std::string_view&&";
	const char* SUFFIX_std_string_view_clvref = "_const_std::string_view&";
}

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

//---------------------------StrMute--------------------------------

std::string StrMute::reverseString()
{
	return std::string(REV_STR_VOID_RET) + SUFFIX_void;
}


std::string StrMute::reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_const_char_ptr;
}


std::string StrMute::reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string;
}


std::string StrMute::reverseString(std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_lvref;
}


std::string StrMute::reverseString(std::string&& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_rvref;
}


std::string StrMute::reverseString(const std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_clvref;
}


std::string StrMute::reverseString(std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_ptr;
}


std::string StrMute::reverseString(const std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_cptr;
}


std::string StrMute::revStrConstRefArg(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref;
}


std::string StrMute::revStrRValueRefArg(std::string_view&& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_rvref;
}


std::string StrMute::revStrNonConstRefArg(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref;
}


std::string StrMute::revStrOverloadValCRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view;
}


std::string StrMute::revStrOverloadValCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref;
}


std::string StrMute::revStrOverloadValRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view;
}


std::string StrMute::revStrOverloadValRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref;
}


std::string StrMute::revStrOverloadRefAndCRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref;
}


std::string StrMute::revStrOverloadRefAndCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref;
}


//---------------------------StrConst--------------------------------

std::string StrConst::reverseString() const
{
	return std::string(REV_STR_VOID_RET) + SUFFIX_void + SUFFIX_const;
}


std::string StrConst::reverseString(const char* pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_const_char_ptr + SUFFIX_const;
}


std::string StrConst::reverseString(std::string pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string + SUFFIX_const;
}


std::string StrConst::reverseString(std::string& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_lvref + SUFFIX_const;
}


std::string StrConst::reverseString(std::string&& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_rvref + SUFFIX_const;
}


std::string StrConst::reverseString(const std::string& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_clvref + SUFFIX_const;
}


std::string StrConst::reverseString(std::string* pStr) const
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_ptr + SUFFIX_const;
}


std::string StrConst::reverseString(const std::string* pStr) const
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_cptr + SUFFIX_const;
}


std::string StrConst::revStrConstRefArg(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref + SUFFIX_const;
}


std::string StrConst::revStrRValueRefArg(std::string_view&& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_rvref + SUFFIX_const;
}


std::string StrConst::revStrNonConstRefArg(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref + SUFFIX_const;
}


std::string StrConst::revStrOverloadValCRef(std::string_view pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view + SUFFIX_const;
}


std::string StrConst::revStrOverloadValCRef(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref + SUFFIX_const;
}


std::string StrConst::revStrOverloadValRef(std::string_view pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view + SUFFIX_const;
}


std::string StrConst::revStrOverloadValRef(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref + SUFFIX_const;
}


std::string StrConst::revStrOverloadRefAndCRef(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref + SUFFIX_const;
}


std::string StrConst::revStrOverloadRefAndCRef(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref + SUFFIX_const;
}


//---------------------------StrStatic--------------------------------

std::string StrStatic::reverseString()
{
	return std::string(REV_STR_VOID_RET) + SUFFIX_void + SUFFIX_static;
}


std::string StrStatic::reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_const_char_ptr + SUFFIX_static;
}


std::string StrStatic::reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string + SUFFIX_static;
}


std::string StrStatic::reverseString(std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_lvref + SUFFIX_static;
}


std::string StrStatic::reverseString(std::string&& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_rvref + SUFFIX_static;
}


std::string StrStatic::reverseString(const std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_clvref + SUFFIX_static;
}


std::string StrStatic::reverseString(std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_ptr + SUFFIX_static;
}


std::string StrStatic::reverseString(const std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_cptr + SUFFIX_static;
}


std::string StrStatic::revStrConstRefArg(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref + SUFFIX_static;
}


std::string StrStatic::revStrRValueRefArg(std::string_view&& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_rvref + SUFFIX_static;
}


std::string StrStatic::revStrNonConstRefArg(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref + SUFFIX_static;
}


std::string StrStatic::revStrOverloadValCRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view + SUFFIX_static;
}


std::string StrStatic::revStrOverloadValCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref + SUFFIX_static;
}


std::string StrStatic::revStrOverloadValRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view + SUFFIX_static;
}


std::string StrStatic::revStrOverloadValRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref + SUFFIX_static;
}


std::string StrStatic::revStrOverloadRefAndCRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_lvref + SUFFIX_static;
}


std::string StrStatic::revStrOverloadRefAndCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_std_string_view_clvref + SUFFIX_static;
}