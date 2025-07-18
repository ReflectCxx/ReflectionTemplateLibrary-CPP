
#include "RObjectBuilder.h"

namespace rtl::detail 
{
	std::atomic<std::size_t> RObjectBuilder::m_reflectedInstanceCount = 0;
}