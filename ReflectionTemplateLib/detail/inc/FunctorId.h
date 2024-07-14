#pragma once

#include "TypeId.h"
#include "Constants.h"

namespace rtl 
{
	namespace detail 
	{
		class FunctorId
		{
			const std::size_t m_index;
			const std::size_t m_returnId;
			const std::size_t m_recordId;
			const std::size_t m_containerId;

		public:

			FunctorId() 
				: m_index(-1)
				, m_returnId(TypeId<>::None)
				, m_recordId(TypeId<>::None)
				, m_containerId(TypeId<>::None) {
			}

			FunctorId(const std::size_t& pIndex, const std::size_t& pReturnId,
				  const std::size_t& pRecordId, const std::size_t& pContainerId)
				: m_index(pIndex)
				, m_returnId(pReturnId)
				, m_recordId(pRecordId)
				, m_containerId(pContainerId) {
			}

			GETTER(std::size_t, Index, m_index)
			GETTER(std::size_t, SignatureId, m_containerId)
			
			std::size_t getHashCode() const;
		};
	}
}