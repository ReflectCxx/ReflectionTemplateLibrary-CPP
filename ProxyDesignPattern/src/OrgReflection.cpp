#include "OrgReflection.h"
#include "Original.h"

using namespace rtl::builder;
using namespace rtl::access;

namespace proxy_test 
{
	OrgReflection::OrgReflection() :CxxMirror(
		{
			Reflect().record<Original>("Original").constructor().build(),
			Reflect().record<Original>("Original").method("getClassId").build(&Original::getClassId),
			Reflect().record<Original>("Original").method("getSquareRoot").build(&Original::getSquareRoot)
		})
	{}
}