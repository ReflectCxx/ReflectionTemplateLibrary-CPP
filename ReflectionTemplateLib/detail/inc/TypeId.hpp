#pragma once

#include <atomic>

#include "TypeId.h"

namespace rtl {

	namespace detail 
	{
		extern std::atomic<std::size_t> g_typeIdCounter;

		template<class _type>
		const std::size_t TypeId<_type>::m_typeId = g_typeIdCounter++ ;
	}
}