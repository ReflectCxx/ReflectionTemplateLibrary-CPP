#pragma once

#include "CxxMirror.h"

namespace rtl_tests {

	struct MyReflection
	{
		static rtl::CxxMirror& instance();
	};
}