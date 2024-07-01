
#include "TypeId.h"
#include "Constants.h"

namespace rtl {

	namespace detail
	{
		std::size_t g_signIdCounter = int(Type::NONE) + 1;
		std::size_t g_typeIdCounter = int(Type::NONE) + 1;
	}
}