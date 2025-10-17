
#include <complex>
#include <algorithm>

#include "ComplexStrings.h"

namespace complex
{
	static double g_imgNumber;
	static double g_realNumber;

	double getMagnitude()
	{
		std::complex<double> z(g_realNumber, g_imgNumber);
		return std::abs(z);
	}

	void setReal(double pNum) {
		g_realNumber = pNum;
	}

	void setImaginary(double pNum) {
		g_imgNumber = pNum;
	}
}

std::string getComplexNumAsString()
{
	return std::to_string(complex::g_realNumber) + "i" + (std::to_string(complex::g_imgNumber));
}

namespace test_utils {

	const char* SUFFIX_const = "_const";
	const char* SUFFIX_ARG_void = "_arg_void";
	const char* SUFFIX_ARG_const_char_ptr = "_arg_const_char_*";

	const char* SUFFIX_ARG_std_string = "_arg_std::string";

	const char* SUFFIX_ARG_std_string_ptr = "_arg_std::string*";
	const char* SUFFIX_ARG_std_string_cptr = "_arg_const_std::string*";

	const char* SUFFIX_ARG_std_string_lvref = "_arg_std::string&";
	const char* SUFFIX_ARG_std_string_clvref = "_arg_const_std::string&";
	
	const char* SUFFIX_ARG_std_string_rvref = "_arg_std::string&&";

	const char* REV_STR_VOID_RET = "func_reverseString(void)->[return_str]";

	const char* SUFFIX_ARG_std_string_view = "_arg_std::string_view";
	const char* SUFFIX_ARG_std_string_view_lvref = "_arg_std::string_view&";
	const char* SUFFIX_ARG_std_string_view_rvref = "_arg_std::string_view&&";
	const char* SUFFIX_ARG_std_string_view_clvref = "_arg_const_std::string_view&";
}

using namespace test_utils;

std::string reverseString()
{
	return std::string(REV_STR_VOID_RET) + SUFFIX_ARG_void;
}


std::string reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_const_char_ptr;
}


std::string reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string;
}


std::string reverseString(std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_lvref;
}


std::string reverseString(std::string&& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_rvref;
}


std::string reverseString(const std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_clvref;
}


std::string reverseString(std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_ptr;
}


std::string reverseString(const std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_cptr;
}


std::string revStrConstRefArg(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref;
}


std::string revStrRValueRefArg(std::string_view&& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_rvref;
}


std::string revStrNonConstRefArg(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref;
}


std::string revStrOverloadValCRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view;
}


std::string revStrOverloadValCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref;
}


std::string revStrOverloadValRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view;
}


std::string revStrOverloadValRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref;
}


std::string revStrOverloadRefAndCRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref;
}


std::string revStrOverloadRefAndCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref;
}

//---------------------------StringM--------------------------------

std::string StringM::reverseString()
{
	return std::string(REV_STR_VOID_RET) + SUFFIX_ARG_void;
}


std::string StringM::reverseString(const char* pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_const_char_ptr;
}


std::string StringM::reverseString(std::string pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string;
}


std::string StringM::reverseString(std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_lvref;
}


std::string StringM::reverseString(std::string&& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_rvref;
}


std::string StringM::reverseString(const std::string& pStr)
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_clvref;
}


std::string StringM::reverseString(std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_ptr;
}


std::string StringM::reverseString(const std::string* pStr)
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_cptr;
}


std::string StringM::revStrConstRefArg(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref;
}


std::string StringM::revStrRValueRefArg(std::string_view&& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_rvref;
}


std::string StringM::revStrNonConstRefArg(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref;
}


std::string StringM::revStrOverloadValCRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view;
}


std::string StringM::revStrOverloadValCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref;
}


std::string StringM::revStrOverloadValRef(std::string_view pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view;
}


std::string StringM::revStrOverloadValRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref;
}


std::string StringM::revStrOverloadRefAndCRef(std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref;
}


std::string StringM::revStrOverloadRefAndCRef(const std::string_view& pStr)
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref;
}


//---------------------------StringC--------------------------------

std::string StringC::reverseString() const
{
	return std::string(REV_STR_VOID_RET) + SUFFIX_ARG_void + SUFFIX_const;
}


std::string StringC::reverseString(const char* pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_const_char_ptr + SUFFIX_const;
}


std::string StringC::reverseString(std::string pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string + SUFFIX_const;
}


std::string StringC::reverseString(std::string& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_lvref + SUFFIX_const;
}


std::string StringC::reverseString(std::string&& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_rvref + SUFFIX_const;
}


std::string StringC::reverseString(const std::string& pStr) const
{
	std::string retStr = pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_clvref + SUFFIX_const;
}


std::string StringC::reverseString(std::string* pStr) const
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_ptr + SUFFIX_const;
}


std::string StringC::reverseString(const std::string* pStr) const
{
	std::string retStr = *pStr;
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_cptr + SUFFIX_const;
}


std::string StringC::revStrConstRefArg(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref + SUFFIX_const;
}


std::string StringC::revStrRValueRefArg(std::string_view&& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_rvref + SUFFIX_const;
}


std::string StringC::revStrNonConstRefArg(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref + SUFFIX_const;
}


std::string StringC::revStrOverloadValCRef(std::string_view pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view + SUFFIX_const;
}


std::string StringC::revStrOverloadValCRef(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref + SUFFIX_const;
}


std::string StringC::revStrOverloadValRef(std::string_view pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view + SUFFIX_const;
}


std::string StringC::revStrOverloadValRef(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref + SUFFIX_const;
}


std::string StringC::revStrOverloadRefAndCRef(std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_lvref + SUFFIX_const;
}


std::string StringC::revStrOverloadRefAndCRef(const std::string_view& pStr) const
{
	std::string retStr(pStr);
	std::reverse(retStr.begin(), retStr.end());
	return retStr + SUFFIX_ARG_std_string_view_clvref + SUFFIX_const;
}