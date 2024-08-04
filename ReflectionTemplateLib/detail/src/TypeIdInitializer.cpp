
#include <atomic>

#include "TypeId.h"
#include "ReflectionBuilder.h"

namespace rtl 
{
	namespace detail 
	{
		//type id counter, statically initializes a unique-id to TypeId<...>.
		std::atomic<std::size_t> g_typeIdCounter = TypeId<>::None + 1;

		//type id counter, statically initializes a unique-id to FunctorContainer<...> and MethodContainer<...>.
		std::atomic<std::size_t> g_containerIdCounter = TypeId<>::None + 1;
	}
}