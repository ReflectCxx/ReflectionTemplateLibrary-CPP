#include "OrgReflection.h"
#include "Original.h"

using namespace rtl::builder;
using namespace rtl::access;

namespace proxy_test 
{
	OrgReflection::OrgReflection() :CxxMirror(
		{
			Reflect().record<Original>("Original").constructor().build(),
			Reflect().record<Original>("Original").method("getClassName").build(&Original::getClassName),
			Reflect().record<Original>("Original").method("getSquareRoot").build(&Original::getSquareRoot),
			Reflect().record<Original>("Original").method("setNodeName").build(&Original::setNodeName),
			Reflect().record<Original>("Original").method("getNodeName").build(&Original::getNodeName)
		})
	{}
}