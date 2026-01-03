
#include <algorithm>

#include "StringConstOverload.h"
#include "../../CxxTestUtils/inc/GlobalTestUtils.h"

using namespace test_utils;

//---------------------------StrConstOverload--------------------------------

std::string StrConstOverload::reverseString()
{
	return std::string(struct_) + REV_STR_VOID_RET + SUFFIX_void;
}


std::string StrConstOverload::reverseString() const
{
	return std::string(struct_) + REV_STR_VOID_RET + SUFFIX_void + SUFFIX_const;
}