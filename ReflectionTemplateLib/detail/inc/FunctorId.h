#pragma once

#include "Constants.h"

namespace rtl 
{
	namespace detail 
	{
		class FunctorId
		{
			std::size_t m_index;
			std::size_t m_hashCode;
			std::size_t m_signatureId;
			std::size_t m_paramsCount;

		public:

			FunctorId(const std::size_t& pIndex, const std::size_t& pHashCode, const std::size_t& pSignId, const std::size_t& pParamsCount)
				: m_index(pIndex)
				, m_hashCode(pHashCode)
				, m_signatureId(pSignId)
				, m_paramsCount(pParamsCount) {
			}

			GETTER(std::size_t, Index, m_index)
			GETTER(std::size_t, HashCode, m_hashCode)
			GETTER(std::size_t, SignatureId, m_signatureId)
		};
	}
}