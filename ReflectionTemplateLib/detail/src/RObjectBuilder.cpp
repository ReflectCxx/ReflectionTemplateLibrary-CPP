
#include "RObjectBuilder.h"

namespace rtl::detail 
{
	std::atomic<std::size_t> RObjectBuilder::m_reflectedInstanceCount = 0;

	const std::size_t RObjectBuilder::reflectedInstanceCount()
	{
		return m_reflectedInstanceCount;
	}
}