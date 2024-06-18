
#include "Function.h"

namespace rtl {

	Function::Function(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction,
			   const std::string& pSignature, const std::size_t& pSignatureId, const std::size_t& pFunctorId, const bool& pIsMemberFunction)
		: m_functorId(pFunctorId)
		, m_signatureId(pSignatureId)
		, m_record(pRecord)
		, m_function(pFunction)
		, m_signature(pSignature)
		, m_namespace(pNamespace)
		, m_isMemberFunction(pIsMemberFunction)
	{
	}
}