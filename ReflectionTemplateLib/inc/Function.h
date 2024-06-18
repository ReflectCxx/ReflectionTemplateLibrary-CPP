#pragma once

#include <string>
#include <memory>

#include "RObject.h"
#include "Constants.h"

namespace rtl {

	class Function
	{
		const std::size_t m_functorId;
		const std::size_t m_signatureId;

		const std::string m_record;
		const std::string m_function;
		const std::string m_signature;
		const std::string m_namespace;

		const bool m_isMemberFunction;

		Function(const std::string& pNamespace, const std::string& pClassName, const std::string& pFuncName, 
			 const std::string& pSignature, const std::size_t& pSignatureId, const std::size_t& pFunctorId, const bool& pIsMemberFunction);

	public:

		Function() = delete;

		GETTER(std::size_t, FunctorId, m_functorId)
		GETTER(std::size_t, SignatureId, m_signatureId)
		GETTER(std::string, RecordName, m_record)
		GETTER(std::string, FunctionName, m_function)
		GETTER(std::string, Signature, m_signature)
		GETTER(std::string, Namespace, m_namespace)

		template<class ..._args>
		std::unique_ptr<RObject> execute(_args...params) const;

		template<class _recordType, class ..._ctorSignature>
		static const Function addConstructor(const std::string& pNamespace, const std::string& pRecord);

		template<class _returnType, class ..._signature>
		static const Function addFunctor(const std::string& pNamespace, const std::string& pRecord,
						 const std::string& pFunction, _returnType(*pFunctor)(_signature...));

		template<class _recordType, class _returnType, class ..._signature>
		static const Function addFunctor(const std::string& pNamespace, const std::string& pRecord,
						 const std::string& pFunction, _returnType(_recordType::* pFunctor)(_signature...));
	};
}