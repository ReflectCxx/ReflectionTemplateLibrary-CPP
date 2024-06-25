#pragma once

#include "ReflectionTemplateLib.h"

#include "TestUtilsBook.h"
#include "TestUtilsDate.h"

struct MyReflection
{
	static rtl::access::CxxMirror& instance();
};
