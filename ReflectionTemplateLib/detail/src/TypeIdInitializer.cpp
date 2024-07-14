#pragma once

#include <atomic>

#include "TypeId.h"
#include "ReflectionBuilder.h"

namespace rtl 
{
	namespace detail 
	{
		std::atomic<std::size_t> g_typeIdCounter = TypeId<>::None + 1;
		std::atomic<std::size_t> g_containerIdCounter = TypeId<>::None + 1;
	}
}