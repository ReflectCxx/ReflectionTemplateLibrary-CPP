#pragma once

#include <string>

namespace rtl {

	class Function
	{
		const std::string m_record;
		const std::string m_namespace;
		const std::size_t m_functorId;
		const std::size_t m_signatureId;
		const std::string m_functionName;

		Function(const std::string& pNamespace, const std::string& pClassName, 
				 const std::size_t& pSignatureId, const std::size_t& pFunctorId, const std::string& pFuncName);
	public:

		Function() = delete;

		const std::size_t& getFunctorId() const;
		const std::string& getNamespace() const;
		const std::string& getRecordName() const;
		const std::size_t& getSignatureId() const;
		const std::string& getFunctionName() const;

		template<class _returnType, class ..._signature>
		static const Function add(	const std::string& pNamespace, const std::string& pRecord, 
									const std::string& pFunction, _returnType(*pFunctor)(_signature...));
	};
}