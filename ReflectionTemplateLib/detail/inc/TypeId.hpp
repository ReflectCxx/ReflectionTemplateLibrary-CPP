#pragma once

#include <atomic>

#include "TypeId.h"

namespace rtl {

	namespace detail 
	{
		extern std::atomic<std::size_t> g_typeIdCounter;

		//statically initialize a unique-id.
		template<class _type>
		const std::size_t TypeId<_type>::m_typeId = g_typeIdCounter.fetch_add(1);
	}
}