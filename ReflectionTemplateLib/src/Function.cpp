
#include "Function.h"

namespace rtl {

	Function::Function(	const std::string& pNamespace, const std::string& pRecord, 
						const std::size_t& pSignatureId, const std::size_t& pFunctorId, const std::string& pFunction)
		: m_record(pRecord)
		, m_namespace(pNamespace)
		, m_functorId(pFunctorId)
		, m_signatureId(pSignatureId)
		, m_functionName(pFunction)
	{
	}

	const std::size_t& Function::getSignatureId() const
	{
		return m_signatureId;
	}

	const std::size_t& Function::getFunctorId() const
	{
		return m_functorId;
	}

	const std::string& Function::getNamespace() const
	{
		return m_namespace;
	}

	const std::string& Function::getRecordName() const
	{
		return m_record;
	}

	const std::string& Function::getFunctionName() const
	{
		return m_functionName;
	}
}