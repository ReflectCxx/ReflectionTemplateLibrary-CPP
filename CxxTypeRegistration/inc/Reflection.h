#pragma once

#include "ReflectionTemplateLib.h"

#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsGlobals.h"

struct MyReflection
{
	static rtl::access::CxxMirror& instance();
};
