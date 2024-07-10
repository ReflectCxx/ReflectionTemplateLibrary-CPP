
#include <cassert>
#include <algorithm>

#include "Function.h"

namespace rtl {

	namespace access 
	{
		Function::Function()
			: m_qualifier(TypeQ::None)
			, m_record("")
			, m_function("")
			, m_signatures("")
			, m_namespace("")
		{
		}


		Function::Function(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction,
				   const std::string& pSignature, const detail::FunctorId& pFunctorId, const TypeQ pQualifier)
			: m_qualifier(pQualifier)
			, m_functorIds({ pFunctorId })
			, m_record(pRecord)
			, m_function(pFunction)
			, m_signatures(pSignature)
			, m_namespace(pNamespace) {
		}


		Function::Function(const Function& pOther, const detail::FunctorId& pFunctorId,
				   const std::function<std::string()>& pGetName)
			: m_qualifier(pOther.m_qualifier)
			, m_functorIds({ pFunctorId })
			, m_record(pOther.m_record)
			, m_function(pGetName())
			, m_signatures("")			//No need to keep this info for implicitly generated functions.
			, m_namespace(pOther.m_namespace) {
		}


		const bool Function::hasSignatureId(const std::size_t& pSignatureId) const
		{
			const auto& itr = std::find_if(m_functorIds.begin(), m_functorIds.end(),
				[pSignatureId](const detail::FunctorId& functorId) {
					return (functorId.getSignatureId() == pSignatureId);
				});
			return itr != m_functorIds.end();
		}


		const bool Function::hasSignatureId(const std::size_t& pSignatureId, std::size_t& pIndex, std::size_t& pHashCode) const
		{
			auto itr = std::find_if(m_functorIds.begin(), m_functorIds.end(),
				[pSignatureId](const detail::FunctorId& functorId) {
					return (functorId.getSignatureId() == pSignatureId);
				});

			if (itr != m_functorIds.end()) {
				pIndex = itr->getIndex();
				pHashCode = itr->getHashCode();
				return true;
			}
			return false;
		}


		void Function::addOverload(const Function& pOtherFunc) const
		{
			const std::size_t& otherFuncSignId = pOtherFunc.m_functorIds[0].getSignatureId();

			auto itr = std::find_if(m_functorIds.begin(), m_functorIds.end(),
				[otherFuncSignId](const detail::FunctorId& functorId) {
					return (functorId.getSignatureId() == otherFuncSignId);
				});

			if (itr != m_functorIds.end()) {
				assert(false && "multiple registration of same function");
			}

			m_functorIds.push_back(pOtherFunc.m_functorIds[0]);
			m_signatures.append("\n" + pOtherFunc.m_signatures);
		}
	}
}