
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


		void Function::sortFunctorsHash() const
		{
			std::sort(m_functorIndex.begin(), m_functorIndex.end(),
				[](const detail::FunctorId& a, const detail::FunctorId& b) {
					return a.getSignatureId() < b.getSignatureId();
				});
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


		const bool Function::hasSignatureId(const std::size_t& pSignId, std::size_t& pIndex, std::size_t& pHashCode) const
		{
			const auto& itr = std::lower_bound(m_functorIndex.begin(), m_functorIndex.end(), pSignId,
				[](const detail::FunctorId& a, const std::size_t& otherSignId) {
					return a.getSignatureId() < otherSignId;
				});

			if (itr != m_functorIndex.end() && itr->getSignatureId() == pSignId) {
				pIndex = itr->getIndex();
				pHashCode = itr->getHashCode();
				return true;
			}
			return false;
		}
	}
}