
#include <cassert>
#include <algorithm>

#include "Function.h"

namespace rtl {

	namespace access 
	{
		Function::Function(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction,
				   const std::string& pSignature, const detail::FunctorId& pFunctorId, const TypeQ pQualifier)
			: m_qualifier(pQualifier)
			, m_functorIndex({ pFunctorId })
			, m_record(pRecord)
			, m_function(pFunction)
			, m_signatures(pSignature)
			, m_namespace(pNamespace) {
		}


		const bool Function::hasSignatureId(const std::size_t& pSignatureId) const
		{
			const auto& itr = std::find_if(m_functorIndex.begin(), m_functorIndex.end(),
				[pSignatureId](const detail::FunctorId& functorId) {
					return (functorId.getSignatureId() == pSignatureId);
				});
			return itr != m_functorIndex.end();
		}


		const bool Function::hasSignatureId(const std::size_t& pSignatureId, std::size_t& pIndex, std::size_t& pHashCode) const
		{
			auto itr = std::find_if(m_functorIndex.begin(), m_functorIndex.end(),
				[pSignatureId](const detail::FunctorId& functorId) {
					return (functorId.getSignatureId() == pSignatureId);
				});

			if (itr != m_functorIndex.end()) {
				pIndex = itr->getIndex();
				pHashCode = itr->getHashCode();
				return true;
			}
			return false;
		}


		void Function::addOverload(const Function& pOtherFunc) const
		{
			const std::size_t& otherFuncSignId = pOtherFunc.m_functorIndex[0].getSignatureId();

			auto itr = std::find_if(m_functorIndex.begin(), m_functorIndex.end(),
				[otherFuncSignId](const detail::FunctorId& functorId) {
					return (functorId.getSignatureId() == otherFuncSignId);
				});

			if (itr != m_functorIndex.end()) {
				assert(false && "multiple registration of same function");
			}

			m_functorIndex.push_back(pOtherFunc.m_functorIndex[0]);
			m_signatures.append("\n" + pOtherFunc.m_signatures);
		}
	}
}