
#include <algorithm>

#include "Function.h"

namespace rtl {

	namespace access 
	{
		Function::Function(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction,
				   const std::string& pSignature, const std::size_t& pSignatureId, const std::size_t& pFunctorId)
			: m_functorHash({ std::make_pair(pSignatureId, pFunctorId) })
			, m_record(pRecord)
			, m_function(pFunction)
			, m_signatures(pSignature)
			, m_namespace(pNamespace)
		{
		}


		void Function::addOverload(const Function& pOtherFunc) const
		{
			m_functorHash.push_back(pOtherFunc.m_functorHash[0]);
			m_signatures.append("\n" + pOtherFunc.m_signatures);
		}


		void Function::sortFunctorsHash() const
		{
			std::sort(m_functorHash.begin(), m_functorHash.end(),
				[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
					return a.first < b.first;
				});
		}


		const bool Function::hasSignatureId(const signatureId pSignId, std::pair<signatureId, functorIndex>& pFuncHash) const
		{
			const auto& itr = std::lower_bound(m_functorHash.begin(), m_functorHash.end(), std::make_pair(pSignId, 0),
				[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
					return a.first < b.first;
				});

			if (itr != m_functorHash.end() && itr->first == pSignId) {
				pFuncHash = *itr;
				return true;
			}

			return false;
		}
	}
}