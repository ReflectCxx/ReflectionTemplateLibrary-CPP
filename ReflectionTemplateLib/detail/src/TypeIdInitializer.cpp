#pragma once

#include "TypeId.h"

namespace rtl 
{
	namespace detail 
	{
		std::size_t g_typeIdCounter = TypeId<>::None + 1;
		std::size_t g_containerIdCounter = TypeId<>::None + 1;
	}
}