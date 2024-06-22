#pragma once

#include "ReflectionTemplateLib.h"

namespace rtl_tests {

	struct MyReflection
	{
		static rtl::access::CxxMirror& instance();
	};
}