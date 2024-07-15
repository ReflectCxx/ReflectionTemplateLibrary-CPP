
#include "FunctorId.h"

namespace rtl
{
	namespace detail
	{
		std::size_t FunctorId::getHashCode() const
		{
			return std::stoull(std::to_string(m_containerId) +
					   std::to_string(m_index) +
					   std::to_string(m_recordId) +
					   std::to_string(m_returnId));
		}
	}
}