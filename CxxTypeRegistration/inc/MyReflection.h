#pragma once

#include "ReflectionTemplateLib.h"

struct MyReflection
{
	static rtl::access::CxxMirror& instance();
};
