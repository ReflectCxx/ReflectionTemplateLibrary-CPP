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
			FunctorType m_functorType;

		public:

			FunctorId() 
				: m_index(-1)
				, m_hashCode(-1)
				, m_signatureId(0)
				, m_paramsCount(-1)
				, m_functorType(FunctorType::None) {
			}

			FunctorId(const std::size_t& pIndex, const std::size_t& pHashCode, const std::size_t& pSignId, 
				  const std::size_t& pParamsCount, const FunctorType& pFunctorType)
				: m_index(pIndex)
				, m_hashCode(pHashCode)
				, m_signatureId(pSignId)
				, m_paramsCount(pParamsCount)
				, m_functorType(pFunctorType) {
			}

			GETTER(std::size_t, Index, m_index)
			GETTER(std::size_t, HashCode, m_hashCode)
			GETTER(std::size_t, SignatureId, m_signatureId)
			GETTER(FunctorType, FunctorType, m_functorType)
		};
	}
}